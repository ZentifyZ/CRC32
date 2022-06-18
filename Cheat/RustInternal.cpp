#include "pch.h"
#include "Scan.h"
#include "GetModule.h"
#include "Bypass/Header/AAnticheat.h"
#include "Internal/Header/Detour.h"
#include "Header/WndProcHandler.h"
#include "PresentImpl.h"
#include "RustInternal.h"
#include "detours.h"

BOOL Rust::InitializeRust()
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		if (!Rust::FindAllPatterns()) { Ulog("%s - Failed to find patterns.", __FUNCTION__); return false; }
		if (!Rust::HookAllFunctions()) { Ulog("%s - Failed to hook target function.", __FUNCTION__); return false; }

		Ulog("%s - Initialization completed successfully.", __FUNCTION__);

		return true;
	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers)
		{
			Ulog("Exception (%lx) caught in %s @ (%p). Base (%p) - (%p)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress, Globals::g_GameAssemblyBase, Globals::g_Module
			);
		}
	}
	return false;
}
BOOL Rust::FindAllPatterns()
{
	Globals::g_RustClientBase = (UINT_PTR)GetModuleHandleA(xorstr_("RustClient.exe"));
	Globals::g_UnityPlayerBase = (UINT_PTR)GetModuleHandleA(xorstr_("UnityPlayer.dll"));
	Globals::g_GameAssemblyBase = (UINT_PTR)GetModuleHandleA(xorstr_("GameAssembly.dll"));
	Globals::g_DxgiModuleBase = (UINT_PTR)GetModuleHandleA(xorstr_("dxgi.dll"));

	if (!Globals::g_RustClientBase) {
		Ulog("%s - g_RustClientBase is null.", __FUNCTION__); return 0;
	}

	if (!Globals::g_UnityPlayerBase) {
		Ulog("%s - g_UnityPlayerBase is null.", __FUNCTION__); return 0;
	}

	if (!Globals::g_GameAssemblyBase) {
		Ulog("%s - g_GameAssemblyBase is null.", __FUNCTION__); return 0;
	}

	if (!Globals::g_DxgiModuleBase) {
		Ulog("%s - g_DxgiModuleBase is null.", __FUNCTION__); return 0;
	}

	MODULEINFO RustClientModuleInfo;
	BOOL bRustClientModuleInfo = GetModuleInformation(GetCurrentProcess(), (HMODULE)Globals::g_RustClientBase, &RustClientModuleInfo, sizeof(RustClientModuleInfo));

	if (!bRustClientModuleInfo) {
		Ulog("%s - GetModuleInformation failed for RustClientModuleInfo with code 0x%lx.", __FUNCTION__, GetLastError()); return 0;
	}

	Globals::g_RustClientSize = RustClientModuleInfo.SizeOfImage;

	auto RustClientTextSection = Internal::GetImageSection(Globals::g_RustClientBase, ".text");

	if (!RustClientTextSection)
	{
		Ulog("%s - Could not resolve RustClient.exe' .text section.", __FUNCTION__);
		return 0;
	}

	Globals::g_RustClientTextBase = Globals::g_RustClientBase + RustClientTextSection->VirtualAddress;
	Globals::g_RustClientTextSize = RustClientTextSection->Misc.VirtualSize;

	MODULEINFO DXGIModuleInfo;
	BOOL bDXGIModuleInfo = GetModuleInformation(GetCurrentProcess(), (HMODULE)Globals::g_DxgiModuleBase, &DXGIModuleInfo, sizeof(DXGIModuleInfo));

	if (!bDXGIModuleInfo) {
		Ulog("%s - GetModuleInformation failed for DXGIModuleInfo with code 0x%lx.", __FUNCTION__, GetLastError()); return 0;
	}

	Globals::g_DxgiModuleSize = DXGIModuleInfo.SizeOfImage;

	MODULEINFO UnityPlayerInfo;
	BOOL UnityBaseInfo = GetModuleInformation(GetCurrentProcess(), (HMODULE)Globals::g_UnityPlayerBase, &UnityPlayerInfo, sizeof(UnityPlayerInfo));

	if (!UnityBaseInfo) {
		Ulog("%s - GetModuleInformation failed for UnityPlayerInfo with code 0x%lx.", __FUNCTION__, GetLastError()); return 0;
	}

	Globals::g_UnityPlayerSize = UnityPlayerInfo.SizeOfImage;

	MODULEINFO GameAssemblyInfo;
	BOOL GameAssemblyBaseInfo = GetModuleInformation(GetCurrentProcess(), (HMODULE)Globals::g_GameAssemblyBase, &GameAssemblyInfo, sizeof(GameAssemblyInfo));

	if (!GameAssemblyBaseInfo) {
		Ulog("%s - GetModuleInformation failed for GameAssemblyInfo with code 0x%lx.", __FUNCTION__, GetLastError()); return 0;
	}

	Globals::g_GameAssemblySize = GameAssemblyInfo.SizeOfImage;

	// -------------------------------------------------------------------------------------------
	// --------------------------------- Functions Pattern Scans ---------------------------------
	// -------------------------------------------------------------------------------------------

	// PresentImpl_ function used for rendering - only apply to DirectX 11
	//

	Globals::Functions::g_PresentImplementation = Internal::FindPatternIDA(Globals::g_DxgiModuleBase, bDXGIModuleInfo ? DXGIModuleInfo.SizeOfImage : 0x91000,
		xorstr_("48 8b c4 57 41 54 41 55 41 56 41 57 48 83 ec 70 48 c7 40 ? ? ? ? ? 48 89 58 10 48 89 68 18 48 89 70 20 4d 8b e1"));

	if (!Globals::Functions::g_PresentImplementation)
	{
		// Double sig it for extra security :)
		Globals::Functions::g_PresentImplementation = Internal::FindPatternIDA(Globals::g_DxgiModuleBase, bDXGIModuleInfo ? DXGIModuleInfo.SizeOfImage : 0x91000,
			xorstr_("4c 8b dc 4d 89 4b 20 45 89 43 18"));

		if (!Globals::Functions::g_PresentImplementation)
		{
			// 3 whole dif mutations
			//
			Globals::Functions::g_PresentImplementation = Internal::FindPatternIDA(Globals::g_DxgiModuleBase, bDXGIModuleInfo ? DXGIModuleInfo.SizeOfImage : 0x91000,
				xorstr_("48 8b c4 48 89 58 10 48 89 68 18 48 89 70 20 57 41 54 41 55 41 56 41 57 48 83 ec 70"));

			if (!Globals::Functions::g_PresentImplementation)
			{
				Ulog("%s - g_PresentImplementation is null.", __FUNCTION__); return 0;
			}
		}
	}

	Ulog("%s - g_PresentImplementation is at (%llx).", __FUNCTION__, Globals::Functions::g_PresentImplementation);

	// Unity function that returns dxgi swapchain
	//
	auto fnUnityGetSwapchain = Internal::FindPatternIDA(Globals::g_UnityPlayerBase, Globals::g_UnityPlayerSize, "48 83 ec 28 e8 ? ? ? ? 48 8b 80 a0 03 00 00");

	if (!fnUnityGetSwapchain) { Ulog("%s - fnUnityGetSwapchain is null.", __FUNCTION__); return 0; }

	auto pUnitySwapchain = *reinterpret_cast<PVOID**>(reinterpret_cast<IDXGISwapChain * (__fastcall*)()>(fnUnityGetSwapchain)());

	// Resizebuffer at vtable 13
	//
	Globals::Functions::Original_DxgiResizeBuffer = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT)>(pUnitySwapchain[13]);

	Globals::Functions::g_OriginalWndProcHandler = Internal::FindPatternIDA(Globals::g_UnityPlayerBase, Globals::g_UnityPlayerSize,
		xorstr_("40 55 56 57 41 55 41 56 48 8d 6c 24 c9 48 81 ec a0 00"));

	if (!Globals::Functions::g_OriginalWndProcHandler) { Ulog("%s - g_OriginalWndProcHandler is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_VisUpdateUsingCulling = (void(__fastcall*)(void*, float, bool))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "VisUpdateUsingCulling"));
	if (!Globals::Functions::Original_VisUpdateUsingCulling) { Ulog("%s - Original_VisUpdateUsingCulling is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_OnGUI = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "UnityEngine", "DDraw", "OnGUI"));
	if (!Globals::Functions::Original_OnGUI) { Ulog("%s - Original_OnGUI is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_ClientInput = (void(__fastcall*)(UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "ClientInput"));
	if (!Globals::Functions::Original_ClientInput) { Ulog("%s - Original_ClientInput is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_ShouldShowHud = (bool(__fastcall*)(void))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "UIHUD", "get_shouldShowHud"));
	if (!Globals::Functions::Original_ShouldShowHud) { Ulog("%s - Original_ShouldShowHud is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_GetModifiedAimConeDirection = (Vector3(__fastcall*)(float, Vector3, bool))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "AimConeUtil", "GetModifiedAimConeDirection"));
	if (!Globals::Functions::Original_GetModifiedAimConeDirection) { Ulog("%s - Original_GetModifiedAimConeDirection is null.", __FUNCTION__); return 0; }

	//Globals::Functions::Original_CreateProjectile = (UINT_PTR(__fastcall*)(void*, void*, Vector3, Vector3, Vector3))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "CreateProjectile"));
//	if (!Globals::Functions::Original_CreateProjectile) { Ulog("%s - Original_CreateProjectile is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_FrameUpdate = (void(__fastcall*)(UINT_PTR, bool))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerModel", "FrameUpdate"));
	if (!Globals::Functions::Original_FrameUpdate) { Ulog("%s - Original_FrameUpdate is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_MoveTowards = (Vector3(__fastcall*)(Vector3, Vector3, float))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Vector3", "MoveTowards"));
	if (!Globals::Functions::Original_MoveTowards) { Ulog("%s - Original_MoveTowards is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_AddPunch = (void(__fastcall*)(UINT_PTR, Vector3, float))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "HeldEntity", "AddPunch"));
	if (!Globals::Functions::Original_AddPunch) { Ulog("%s - Original_AddPunch is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_Launch = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "Projectile", "Launch"));
	if (!Globals::Functions::Original_Launch) { Ulog("%s - Original_Launch is null.", __FUNCTION__); return 0; }

//	Globals::Functions::Original_LaunchProjectile = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "LaunchProjectile"));
//	if (!Globals::Functions::Original_LaunchProjectile) { Ulog("%s - Original_Launch is null.", __FUNCTION__); return 0; }


	Globals::Functions::Original_EokaDoAttack = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "FlintStrikeWeapon", "DoAttack"));
	if (!Globals::Functions::Original_EokaDoAttack) { Ulog("%s - Original_EokaDoAttack is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_DoAttack = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "DoAttack"));
	if (!Globals::Functions::Original_DoAttack) { Ulog("%s - Original_DoAttack is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_SetFlying = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Rust.Data", "", "ModelState", "set_flying"));
	if (!Globals::Functions::Original_SetFlying) { Ulog("%s - Original_SetFlying is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_UpdateGravity = (void(__fastcall*)(UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerWalkMovement", "UpdateGravity"));
	if (!Globals::Functions::Original_UpdateGravity) { Ulog("%s - Original_UpdateGravity is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_EditViewAngles = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "EditViewAngles"));
	if (!Globals::Functions::Original_EditViewAngles) { Ulog("%s - Original_EditViewAngles is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_OnCameraPositionChanged = (void(__fastcall*)(UINT_PTR, UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseViewModel", "OnCameraPositionChanged"));
	if (!Globals::Functions::Original_OnCameraPositionChanged) { Ulog("%s - Original_OnCameraPositionChanged is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_ViewModelPlay = (void(__fastcall*)(UINT_PTR, pUncStr, int))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "ViewModel", "Play"));
	if (!Globals::Functions::Original_ViewModelPlay) { Ulog("%s - Original_ViewModelPlay is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_CanHoldItems = (bool(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseMountable", "CanHoldItems"));
	if (!Globals::Functions::Original_CanHoldItems) { Ulog("%s - Origina_CanHoldItems is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_DoHit = (bool(__fastcall*)(UINT_PTR, UINT_PTR, Vector3, Vector3))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "Projectile", "DoHit"));
	if (!Globals::Functions::Original_DoHit) { Ulog("%s - Original_DoHit is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_HandleRunDuckCrawl = (void(__fastcall*)(UINT_PTR, UINT_PTR, bool, bool, bool))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerWalkMovement", "HandleRunDuckCrawl"));
	if (!Globals::Functions::Original_HandleRunDuckCrawl) { Ulog("%s - Original_HandleRunDuckCrawl is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_CanAttack = (bool(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "CanAttack"));
	if (!Globals::Functions::Original_CanAttack) { Ulog("%s - Original_CanAttack is null.", __FUNCTION__); return 0; }

	//Globals::Functions::Original_SendClientTick = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "SendClientTick"));
	//if (!Globals::Functions::Original_SendClientTick) { Ulog("%s - Original_SendClientTick is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_OnLand = (void(__fastcall*)(UINT_PTR, float))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "OnLand"));
	if (!Globals::Functions::Original_OnLand) { Ulog("%s - Original_OnLand is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_DoHitNotify = (void(__fastcall*)(UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseCombatEntity", "DoHitNotify"));
	if (!Globals::Functions::Original_DoHitNotify) { Ulog("%s - Original_DoHitNotify is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_OnAttacked = (void(__fastcall*)(UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "OnAttacked"));
	if (!Globals::Functions::Original_OnAttacked) { Ulog("%s - Original_OnAttacked is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_GetIsHeadshot = (bool(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "HitInfo", "get_isHeadshot"));
	if (!Globals::Functions::Original_GetIsHeadshot) { Ulog("%s - Original_GetIsHeadshot is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_SendProjectileAttack = (void(__fastcall*)(UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "SendProjectileAttack"));
	if (!Globals::Functions::Original_SendProjectileAttack) { Ulog("%s - Original_SendProjectileAttack is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_ProjectileMovement = (void(__fastcall*)(UINT_PTR, float))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "Projectile", "DoMovement"));
	if (!Globals::Functions::Original_ProjectileMovement) { Ulog("%s - Original_ProjectileMovement is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_IsWaterMaterial = (bool(__fastcall*)(UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "Projectile", "IsWaterMaterial"));
	if (!Globals::Functions::Original_IsWaterMaterial) { Ulog("%s - Original_IsWaterMaterial is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_DoFirstPersonCamera_hk = (void(__fastcall*)(UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerEyes", "DoFirstPersonCamera"));
	if (!Globals::Functions::Original_DoFirstPersonCamera_hk) { Ulog("%s - Original_DoFirstPersonCamera_hk is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_HandleJumping = (void(__fastcall*)(UINT_PTR, UINT_PTR, bool, bool))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerWalkMovement", "HandleJumping"));
	if (!Globals::Functions::Original_HandleJumping) { Ulog("%s - Original_HandleJumping is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_SendClientTick = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "SendClientTick"));
	if (!Globals::Functions::Original_SendClientTick) { Ulog("%s - Original_SendClientTick is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_EyePositionForPlayer = (Vector3(__fastcall*)(UINT_PTR, UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseMountable", "EyePositionForPlayer"));
	if (!Globals::Functions::Original_EyePositionForPlayer) { Ulog("%s - Original_EyePositionForPlayer is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_BodyLeanOffset = (Vector3(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerEyes", "get_BodyLeanOffset"));
	if (!Globals::Functions::Original_BodyLeanOffset) { Ulog("%s - Original_GetRandomVelocity is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_GetRandomVelocity = (float(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "ItemModProjectile", "GetRandomVelocity"));
	if (!Globals::Functions::Original_GetRandomVelocity) { Ulog("%s - Original_GetRandomVelocity is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_LaunchProjectile = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "LaunchProjectile"));
	if (!Globals::Functions::Original_LaunchProjectile) { Ulog("%s - Original_Launch is null.", __FUNCTION__); return 0; }

	Globals::Functions::Original_UpdateVelocity = (void(__fastcall*)(UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerWalkMovement", "UpdateVelocity"));
	if (!Globals::Functions::Original_UpdateVelocity) { Ulog("%s - PlayerWalkMovement is null.", __FUNCTION__); return 0; }

	//Globals::Functions::Original_DoFirstPersonCamera_hk = (void(__fastcall*)(UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerEyes", "DoFirstPersonCamera"));
	//if (!Globals::Functions::Original_DoFirstPersonCamera_hk) { Ulog("%s - Original_DoFirstPersonCamera_hk is null.", __FUNCTION__); return 0; }


	// ------------------------------------------------------------------------------------------
	// --------------------------------- Pointers Pattern Scans ---------------------------------
	// ------------------------------------------------------------------------------------------
	Globals::Functions::Original_ConsoleRun = (bool(__fastcall*)(UINT_PTR, UINT_PTR, UINT_PTR))(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Facepunch.Console", "", "ConsoleSystem", "Run"));
	if (!Globals::Functions::Original_ConsoleRun) { Ulog("%s - Original_ConsoleRun is null.", __FUNCTION__); return 0; }

	Globals::g_GlobalObjectManager = (GlobalObjectManagerClass*)Internal::PointerScannerIDA(Globals::g_UnityPlayerBase,
		Globals::g_UnityPlayerSize, 0, 7, 3, xorstr_("48 8b 15 ? ? ? ? 66 39"), xorstr_("Global Object Manager"));

	if (!Globals::g_GlobalObjectManager) {
		Ulog("%s - g_GlobalObjectManager is null.", __FUNCTION__); return 0;
	}

	Globals::g_BaseNetworkable = (BaseNetworkableClass*)Internal::PointerScannerIDA(Globals::g_GameAssemblyBase,
		Globals::g_GameAssemblySize, 0, 7, 3, xorstr_("48 8b 05 ? ? ? ? 48 8b ? b8 00 00 00 48 8b 38 48 85"), xorstr_("Base Networkable"));

	if (!Globals::g_BaseNetworkable) {
		Ulog("%s - g_BaseNetworkable is null.", __FUNCTION__); return 0;
	}

	G::JmpTrampoline = (PVOID)Internal::FindPatternIDA(Globals::g_RustClientTextBase, Globals::g_RustClientTextSize,
		xorstr_("FF 23"));

	if (!G::JmpTrampoline)
	{
		Ulog("%s - Could not find a valid Trampoline for spoofcall.", __FUNCTION__);
		return 0;
	}

	Ulog("%s - JmpTrampoline is (%p).", __FUNCTION__, G::JmpTrampoline);
	Ulog("%s - g_GlobalObjectManager is (%p).", __FUNCTION__, Globals::g_GlobalObjectManager);
	Ulog("%s - g_BaseNetworkable is (%p).", __FUNCTION__, Globals::g_BaseNetworkable);

	// -----------------------------------------------------------------------------------------
	// --------------------------------- Offsets Pattern Scans ---------------------------------
	// -----------------------------------------------------------------------------------------

	return true;

}

BOOL Rust::HookAllFunctions()
{
	if (DetourTransactionBegin() != NO_ERROR) return false;
	if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR) return false;

	if (DetourAttach(&(PVOID&)Globals::Functions::g_PresentImplementation, Hooks::hk_PresentImplementation) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_DxgiResizeBuffer, Hooks::hk_ResizeBuffer) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::g_OriginalWndProcHandler, Hooks::hWndProc) != NO_ERROR) return false;



	if (DetourAttach(&(PVOID&)Globals::Functions::Original_ConsoleRun, Hooks::hk_ConsoleRun) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_HandleJumping, Hooks::hk_HandleJumping) != NO_ERROR) return false;
//	if (DetourAttach(&(PVOID&)Globals::Functions::Original_HasPermission, Hooks::hk_HasPermission) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_DoFirstPersonCamera_hk, Hooks::hk_DoFirstPersonCamera) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_GetRandomVelocity, Hooks::hk_GetRandomVelocity) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_LaunchProjectile, Hooks::hk_LaunchProjectile) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_IsWaterMaterial, Hooks::hk_IsWaterMaterial) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_BodyLeanOffset, Hooks::hk_BodyLeanOffset) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_EyePositionForPlayer, Hooks::hk_EyePositionForPlayer) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_UpdateVelocity, Hooks::hk_UpdateVelocity) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_ProjectileMovement, Hooks::hk_ProjectileMovement) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_SendProjectileAttack, Hooks::hk_SendProjectileAttack) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_FrameUpdate, Hooks::hk_FrameUpdate) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_GetIsHeadshot, Hooks::hk_GetIsHeadshot) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_OnAttacked, Hooks::hk_OnAttacked) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_DoHitNotify, Hooks::hk_DoHitNotify) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_DoHit, Hooks::hk_DoHit) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_OnLand, Hooks::hk_OnLand) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_SendClientTick, Hooks::hk_SendClientTick) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_CanAttack, Hooks::hk_CanAttack) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_HandleRunDuckCrawl, Hooks::hk_HandleRunDuckCrawl) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_CanHoldItems, Hooks::hk_CanHoldItems) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_ViewModelPlay, Hooks::hk_ViewModelPlay) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_EditViewAngles, Hooks::hk_EditViewAngles) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_OnCameraPositionChanged, Hooks::hk_OnCameraPositionChanged) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_DoAttack, Hooks::hk_DoAttack) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_SetFlying, Hooks::hk_SetFlying) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_UpdateGravity, Hooks::hk_UpdateGravity) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_Launch, Hooks::hk_Launch) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_EokaDoAttack, Hooks::hk_EokaDoAttack) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_MoveTowards, Hooks::hk_MoveTowards) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_AddPunch, Hooks::hk_AddPunch) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_ClientInput, Hooks::hk_ClientInput) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_OnGUI, Hooks::hk_OnGUI) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_ShouldShowHud, Hooks::hk_FakeShouldShowHud) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_GetModifiedAimConeDirection, Hooks::hk_FakeGetModifiedAimConeDirection) != NO_ERROR) return false;
//	if (DetourAttach(&(PVOID&)Globals::Functions::Original_CreateProjectile, Hooks::hk_FakeCreateProjectile) != NO_ERROR) return false;
	if (DetourAttach(&(PVOID&)Globals::Functions::Original_VisUpdateUsingCulling, Hooks::hk_FakeVisUpdateUsingCulling) != NO_ERROR) return false;

	if (DetourTransactionCommit() != NO_ERROR) return false;

	return true;
}

BOOL Rust::Unload()
{
	if (DetourTransactionBegin() != NO_ERROR) return false;
	if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR) return false;


	//if (DetourDetach(&(PVOID&)Globals::Functions::Original_ConsoleRun, Hooks::hk_ConsoleRun) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::g_PresentImplementation, Hooks::hk_PresentImplementation) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_DxgiResizeBuffer, Hooks::hk_ResizeBuffer) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::g_OriginalWndProcHandler, Hooks::hWndProc) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_EyePositionForPlayer, Hooks::hk_EyePositionForPlayer) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_BodyLeanOffset, Hooks::hk_BodyLeanOffset) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_HandleJumping, Hooks::hk_HandleJumping) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_LaunchProjectile, Hooks::hk_LaunchProjectile) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_DoFirstPersonCamera_hk, Hooks::hk_DoFirstPersonCamera) != NO_ERROR) return false;
//	if (DetourDetach(&(PVOID&)Globals::Functions::Original_HasPermission, Hooks::hk_HasPermission) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_IsWaterMaterial, Hooks::hk_IsWaterMaterial) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_ProjectileMovement, Hooks::hk_ProjectileMovement) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_SendClientTick, Hooks::hk_SendClientTick) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_SendProjectileAttack, Hooks::hk_SendProjectileAttack) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_UpdateVelocity, Hooks::hk_UpdateVelocity) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_FrameUpdate, Hooks::hk_FrameUpdate) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_GetIsHeadshot, Hooks::hk_GetIsHeadshot) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_OnAttacked, Hooks::hk_OnAttacked) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_DoHitNotify, Hooks::hk_DoHitNotify) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_DoHit, Hooks::hk_DoHit) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_OnLand, Hooks::hk_OnLand) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_CanAttack, Hooks::hk_CanAttack) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_HandleRunDuckCrawl, Hooks::hk_HandleRunDuckCrawl) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_CanHoldItems, Hooks::hk_CanHoldItems) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_ViewModelPlay, Hooks::hk_ViewModelPlay) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_GetRandomVelocity, Hooks::hk_GetRandomVelocity) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_EditViewAngles, Hooks::hk_EditViewAngles) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_OnCameraPositionChanged, Hooks::hk_OnCameraPositionChanged) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_DoAttack, Hooks::hk_DoAttack) != NO_ERROR) return false;
//	if (DetourDetach(&(PVOID&)Globals::Functions::Original_SetFlying, Hooks::hk_SetFlying) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_UpdateGravity, Hooks::hk_UpdateGravity) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_Launch, Hooks::hk_Launch) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_EokaDoAttack, Hooks::hk_EokaDoAttack) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_MoveTowards, Hooks::hk_MoveTowards) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_AddPunch, Hooks::hk_AddPunch) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_ClientInput, Hooks::hk_ClientInput) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_OnGUI, Hooks::hk_OnGUI) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_ShouldShowHud, Hooks::hk_FakeShouldShowHud) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_GetModifiedAimConeDirection, Hooks::hk_FakeGetModifiedAimConeDirection) != NO_ERROR) return false;
	//if (DetourDetach(&(PVOID&)Globals::Functions::Original_CreateProjectile, Hooks::hk_FakeCreateProjectile) != NO_ERROR) return false;
	if (DetourDetach(&(PVOID&)Globals::Functions::Original_VisUpdateUsingCulling, Hooks::hk_FakeVisUpdateUsingCulling) != NO_ERROR) return false;

	UnityEngine::IgnoreLayerCollision(12, 4, true);
	UnityEngine::IgnoreLayerCollision(12, 30, false);
	UnityEngine::IgnoreLayerCollision(12, 11, false);

	UnityEngine::RebuildAll();

	if (UnityEngine::asset_bundle != 0x402402) UnityEngine::UnLoadAssetBundle(UnityEngine::asset_bundle, true);

	if (DetourTransactionCommit() != NO_ERROR) return false;

	__try {
		if (GroundAngle != -1.f)
			LocalPlayer.movement.groundAngle() = GroundAngle;
		if (GroundAngleNew != -1.f)
			LocalPlayer.movement.groundAngleNew() = GroundAngleNew;

		if (CapCrouch != 0.f)
			LocalPlayer.movement.capsuleCenterDucked() = CapCrouch;

		if (Cap != 0.f)
			LocalPlayer.movement.capsuleCenter() = Cap;
		if (MVelocity != 0.f)
			LocalPlayer.movement.maxVelocity() = MVelocity;
	}
	__except (true) {
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return true;
}
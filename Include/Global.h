#pragma once

/*
	 Add all globals here for game engine-related stuff
	 G:: is for internal of the anticheat / bypass / auth / etc
	 but Globals:: is for things in game
*/
struct Vector3;

namespace Globals
{
	//Fully Init


	inline bool Ready = false;

	inline HMODULE g_Module = 0;

	// RustClient.exe
	//
	inline UINT_PTR g_RustClientBase = 0;
	inline UINT_PTR g_RustClientSize = 0;

	inline UINT_PTR g_RustClientTextBase = 0;
	inline UINT_PTR g_RustClientTextSize = 0;

	// Unityplayer
	//
	inline UINT_PTR g_UnityPlayerBase = 0;
	inline UINT_PTR g_UnityPlayerSize = 0;

	// Game Assembly
	//
	inline UINT_PTR g_GameAssemblyBase = 0;
	inline UINT_PTR g_GameAssemblySize = 0;

	// Global Rust Managers
	inline GlobalObjectManagerClass* g_GlobalObjectManager = 0;
	inline BaseNetworkableClass* g_BaseNetworkable = 0;

	// Dxgi module
	//
	inline UINT_PTR g_DxgiModuleBase = 0;
	inline UINT_PTR g_DxgiModuleSize = 0;

	// Inputs
	//
	inline bool PressedKeys[256] = {};

	namespace Settings
	{
		inline BOOL g_bMenu = true;

		inline std::string currentConfig = "Default";
		inline std::vector<std::string> ConfigList = { "Default" };
	}

	namespace Hotkeys
	{
		inline int hotkey_Manipulator = 0;
		inline int hotkey_MenuKey = VK_INSERT;
		inline int hotkey_AimKey = VK_CAPITAL;
		inline int hotkey_SpamKey = 0;
		inline int hotkey_FlyhackKey = 0;
		inline int hotkey_SpiderKey = 0;
		inline int hotkey_SuicideKey = 0;
		inline int hotkey_Zoom = 0;
		inline int hotkey_SilentKey = 0;
		inline int hotkey_AimbotKey = 0;
		inline int hotkey_InstaKill = 0;
		inline int hotkey_lag = VK_CAPITAL;
	}
	namespace FlyHack {
		inline float VFlyhack = 0.0f;
		inline float HFlyhack = 0.0f;
		inline float VMaxFlyhack = 0.0f;
		inline float HMaxFlyhack = 0.0f;
		inline float flyhackPauseTime = 0.0f;
		inline float flyhackDistanceVertical = 110.f;
		inline float flyhackDistanceHorizontal = 110.f;
	}
	// For all the functions we will be scanning for
	namespace Functions
	{
		inline UINT_PTR g_PresentImplementation = 0;
		inline UINT_PTR g_OriginalWndProcHandler = 0;

		inline HRESULT(*Original_DxgiPresent)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
		inline HRESULT(*Original_DxgiResizeBuffer)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);

		inline void(*Original_VisUpdateUsingCulling)(void*, float, bool);
		inline void(*Original_AddPunch)(UINT_PTR, Vector3, float);
		inline float(*Original_GetRandomVelocity)(UINT_PTR);
		inline void(*Original_EokaDoAttack)(UINT_PTR);
		inline void(*Original_HandleJumping)(UINT_PTR, UINT_PTR, bool, bool);
		inline bool(*Original_HasPermission)(UINT_PTR, UINT_PTR);
		inline void(*Original_HandleRunDuckCrawl)(UINT_PTR, UINT_PTR, bool, bool, bool);
		inline void(*Original_DoAttack)(UINT_PTR);
		inline void(*Original_SendClientTick)(UINT_PTR);
		inline void(*Original_UpdateVelocity)(UINT_PTR);
		inline void(*Original_SetFlying)(UINT_PTR);
		inline void(*Original_UpdateGravity)(UINT_PTR, UINT_PTR);
		inline void(*Original_EditViewAngles)(UINT_PTR);
		inline void(*Original_FrameUpdate)(UINT_PTR, bool);
		inline void(*Original_OnCameraPositionChanged)(UINT_PTR, UINT_PTR, UINT_PTR);
		inline void(*Original_ViewModelPlay)(UINT_PTR, pUncStr, int);
		inline bool(*Original_CanHoldItems)(UINT_PTR);
		inline bool(*Original_IsWaterMaterial)(UINT_PTR, UINT_PTR);
		inline bool(*Original_CanAttack)(UINT_PTR);
		inline void(*Original_SendProjectileAttack)(UINT_PTR, UINT_PTR);
		inline bool(*Original_GetIsHeadshot)(UINT_PTR);
		inline void(*Original_ProjectileMovement)(UINT_PTR, float);
		inline void(*Original_OnAttacked)(UINT_PTR, UINT_PTR);
		inline void(*Original_DoHitNotify)(UINT_PTR, UINT_PTR);
		inline void(*Original_OnLand)(UINT_PTR, float);
		inline bool(*Original_DoHit)(UINT_PTR, UINT_PTR, Vector3, Vector3);
		inline void(*Original_Launch)(UINT_PTR);
		inline void(*Original_OnGUI)(UINT_PTR);
		inline void(*Original_ClientInput)(UINT_PTR, UINT_PTR);
		inline bool(*Original_ShouldShowHud)(void);
		inline bool(*Original_ConsoleRun)(UINT_PTR, UINT_PTR, UINT_PTR);
		inline Vector3(*Original_EyePositionForPlayer)(UINT_PTR, UINT_PTR, UINT_PTR);
		inline Vector3(*Original_MoveTowards)(Vector3, Vector3, float);
		inline Vector3(*Original_GetModifiedAimConeDirection)(float, Vector3, bool);
		inline UINT_PTR(*Original_CreateProjectile)(void*, void*, Vector3, Vector3, Vector3);
		inline Vector3(*Original_BodyLeanOffset)(UINT_PTR);
		inline void(*Original_DoFirstPersonCamera_hk)(UINT_PTR, UINT_PTR);
		inline void(*Original_LaunchProjectile)(UINT_PTR);
	}

	// All SwapChain and Window / Rendering related
	namespace Window
	{
		inline IDXGISwapChain* pChain = NULL;
		inline ID3D11Device* pDevice = NULL;
		inline ID3D11DeviceContext* pContext = NULL;
		inline BOOL BeingResized = false;

		inline HWND GameWindow = 0;
	}
}
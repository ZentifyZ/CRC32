#pragma warning(disable : 4530)
#define StrA
#define StrW

#include "pch.h"


#include "Bypass\Header\AAnticheat.h"
#include "RustInternal.h"
#include "Protector\nt_.hpp"
#include "Protector\Processes.h"

// Place detach codes, such as unhooks and unpatching things
// tho generally useless unless you are just testing using loadlib
// other than that, since we will be manualmapping, these things go out the windows
//
auto Detach() -> bool
{
	return true;
}

auto Initialize() -> bool
{
	// This prevent us from crashing the client, use SEH religiously
	//
	__try
	{
		return Rust::InitializeRust();
	}

	__except ([](unsigned int code, struct _EXCEPTION_POINTERS* ep) -> int
		{
			Ulog("Exception happened in (%s) with code %lx - at RIP %p | %p ", __FUNCTION__,
				code, ep->ExceptionRecord->ExceptionAddress, Globals::g_Module);

			return EXCEPTION_EXECUTE_HANDLER;
		}(GetExceptionCode(), GetExceptionInformation()))
	{
	}

		return false;
}

// Initializtion logics goes in here
auto P402K(LPVOID k_credential) -> bool
{
#ifndef P402DISTRIBUTE
	// Dashed out due to creating debug log in IMGUI
	FILE* fp; AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);
#endif // !P402DISTRIBUTE

	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		/* Must run this before everything because we need it to resolve the APIs that we use */
		//
		if (!Internal::DynamicImportWinAPIs())
		{
			Ulog("%s - Failed to resolve dynamic winapis.", __FUNCTION__);
			return true;
		}
		
		if (Initialize())
		{
			Ulog("Welcome [ CRC32 Users ], to Project CRC32 [%p]", Globals::g_Module);
			Ulog("**********************************************************************************\n");
			Globals::Ready = true;
		}
	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers)
		{
#ifdef P402DISTRIBUTE
			wchar_t ErrorMsg[200];
			swprintf_s(ErrorMsg, L"Could not initialized Rust cheat with code 0x%lx | %p | %p", ExceptionCode, Globals::g_Module, ExceptionPointers->ExceptionRecord->ExceptionAddress);
			MessageBox(NULL, ErrorMsg, NULL, MB_OK);
#else
			Ulog("Exception (%lx) caught in %s @ (%p)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress
			);
#endif
		}
	}

	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Globals::g_Module = hModule;
		return P402K(lpReserved);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		return Detach();
	case DLL_PROCESS_DETACH:
		break;
	}
	return true;
}
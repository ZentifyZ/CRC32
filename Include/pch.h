// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#define CreateField(_assembly, _namespace, _class, _field, name, type) bool name(type& flags) { \
	__try \
	{ \
		static UINT_PTR var = 0x402402; \
		if (var == 0x402402) var = Dumper::GetFieldOffet(_assembly, _namespace, _class, _field); \
		flags = *(type*)(Base_ + var); \
		return true; \
	} \
	__except (true) \
	{ \
		Ulog("%s - Exception Occurred.", __FUNCTION__); \
	} \
	return false; \
	}

#define CreateUnSafeField(_assembly, _namespace, _class, _field, name, type) type& name() { \
	__try \
	{ \
		static UINT_PTR var = 0x402402; \
		if (var == 0x402402) var = Dumper::GetFieldOffet(_assembly, _namespace, _class, _field); \
		return *(type*)(Base_ + var); \
	} \
	__except (true) \
	{ \
		Ulog("%s - Exception Occurred.", __FUNCTION__); \
	} \
		auto n = nullptr; \
		return reinterpret_cast<type&>(n); \
	}

#ifndef P402DISTRIBUTE
//#define Ulog( format, ... ) Menu::Print( xorstr_("[ P402K ] " format "\n"), ##__VA_ARGS__)
#define Ulog( format, ... ) printf( xorstr_("[ CRC32 ] " format "\n"), ##__VA_ARGS__ );
#else:
#define Ulog( format, ... ) void(0)
#endif // !P402DISTRIBUTE

#define PSound( sound ) PlaySoundA(sound, NULL, SND_ASYNC);//PlaySound(sound, NULL, SND_ASYNC);

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define SODIUM_STATIC

#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <TlHelp32.h>
#include <algorithm>
#include <iostream>
#include <MMSystem.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <vector>
#include <atomic>
#include <ctype.h>
#include <chrono>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <regex>
#include <thread>
#include <map>
#include <Psapi.h>
#include <intrin.h>
#include <cstdint>
#include <d3d11.h>
#include <WinSock2.h>
#include <string>
#include <limits.h>
#include <list>
#include <filesystem>

#include "CRC32.hpp"

#include "Xorstr.hpp"
#include "Cheat\Header\Variables.h"
#include "RustMath.h"
#include "RustStructs.h"
#include "Global.h"
#include "font.h"
#include "WndProcHandler.h"
#include "Internal\Header\Imports.h"
#include "Bypass\Header\Spoofcall.h"
#include "json.hpp"
#include "imgui.h"
#include "Menu\DirectGUI\imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "SDK\Dumper.h"
#include "Memory.h"
#include "UnityEngineSDK.h"
#include "Weapons.h"
#include "BasePlayer.h"
#include "Target.hpp"


#include "RustVisual.h"
#include "Drawing.h"
#include "Menu\Menu.h"
#include "RustHooks.h"
#include "AntiHack.hpp"
#endif //PCH_H

// List of Server ID Code to send to the server for reporting as well as authentication
//
#define AUTHENTICATION_CODE     1
#define BAD_PROCESS_FOUND       2
#define BAD_WINDOWS_FOUND       3
#define FAILED_SYSCALL          4
#define WINDOW_LIST_EMPTY       5

// RUSTCLIENT.exe

namespace G
{
	// Anticheat Globals
	inline UINT_PTR EAC_UM_BASE = 0;
	inline SIZE_T   EAC_UM_SIZE = 0;
	inline UINT_PTR EAC_UM_DllEntry = 0;

	// Cheat related globals
	inline HMODULE  g_Module = 0;
	inline UINT_PTR g_ModuleSize = 0;

	// Game related globals
	inline UINT_PTR g_RustClientBase = 0;
	inline UINT_PTR g_RustClientSize = 0;

	// Cheat User related globals
	inline signed int  g_Tier = 0;
	inline const char* g_Username = 0;

	// Stealth globals for hooking shellcode
	// inline UINT_PTR g_CurrentGameBufferCursor = 0;

	// Jmp Trampoline we will be using for any sort of spoofcalling
	inline PVOID JmpTrampoline = 0;
};

#include "pch.h"

// Include all of your supported DX versions here clients here
//

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "RustInternal.h"
#include "Header/WndProcHandler.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK Hooks::hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
			Globals::PressedKeys[VK_LBUTTON] = true;
			break;
		case WM_LBUTTONUP:
			Globals::PressedKeys[VK_LBUTTON] = false;
			break;
		case WM_RBUTTONDOWN:
			Globals::PressedKeys[VK_RBUTTON] = true;
			break;
		case WM_RBUTTONUP:
			Globals::PressedKeys[VK_RBUTTON] = false;
			break;
		case WM_MBUTTONDOWN:
			Globals::PressedKeys[VK_MBUTTON] = true;
			break;
		case WM_MBUTTONUP:
			Globals::PressedKeys[VK_MBUTTON] = false;
			break;
		case WM_KEYDOWN:
			Globals::PressedKeys[wParam] = true;
			break;
		case WM_KEYUP:
			Globals::PressedKeys[wParam] = false;
			break;
		case WM_XBUTTONDOWN:
		{
			UINT button = GET_XBUTTON_WPARAM(wParam);
			if (button == XBUTTON1)
			{
				Globals::PressedKeys[VK_XBUTTON1] = true;
			}
			else if (button == XBUTTON2)
			{
				Globals::PressedKeys[VK_XBUTTON2] = true;
			}
			break;
		}
		case WM_XBUTTONUP:
		{
			UINT button = GET_XBUTTON_WPARAM(wParam);
			if (button == XBUTTON1)
			{
				Globals::PressedKeys[VK_XBUTTON1] = false;
			}
			else if (button == XBUTTON2)
			{
				Globals::PressedKeys[VK_XBUTTON2] = false;
			}
			break;
		}
		}

		//deactivate
		if (uMsg == WM_KEYUP || uMsg == WM_SYSKEYUP)
		{
			if (wParam == Globals::Hotkeys::hotkey_MenuKey)
			{
				Globals::Settings::g_bMenu = !Globals::Settings::g_bMenu;
			}
			else if (wParam == Globals::Hotkeys::hotkey_AimKey)
			{
				Globals::PressedKeys[Globals::Hotkeys::hotkey_AimKey] = false;
			}

#ifndef P402DISTRIBUTE
			if (wParam == VK_HOME)
			{
				Ulog("%s - Detaching cheat.", __FUNCTION__);
				Rust::Unload();
			}
#endif
		}

		// activate
		if (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN)
		{
			if (wParam == Globals::Hotkeys::hotkey_AimKey)
			{
				Globals::PressedKeys[Globals::Hotkeys::hotkey_AimKey] = true;
			}
		}

		// Disable tabbing in case it fuck with hotkey
		if ((Globals::Settings::g_bMenu) && wParam != VK_TAB)
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers)
		{
			Ulog("Exception (%lx) caught in %s @ (%p) (%llx)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress,
				Globals::g_GameAssemblyBase
			);
		}
	}

	return spoof_call(CallWindowProc, (WNDPROC)Globals::Functions::g_OriginalWndProcHandler, hWnd, uMsg, wParam, lParam);
}
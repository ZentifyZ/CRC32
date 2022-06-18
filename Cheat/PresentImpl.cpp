#include "pch.h"
#include "Menu/Menu.h"
#include "PresentImpl.h"

UINT64 Hooks::hk_PresentImplementation(IDXGISwapChain* pChain, void* unk1, void* unk2, void* unk3, void* unk4, void* unk5, void* unk6)
{
	typedef __int64(__fastcall* t_PresentImpl)(IDXGISwapChain* pSwapChain, void* unk1, void* unk2, void* unk3, void* unk4, void* unk5, void* unk6);

	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		static bool skipped = true;
		if (skipped)
		{
			Visuals::SyncedThread();
			skipped = false;
		}
		else
		{
			skipped = true;
		}

		Menu::Wrapper(pChain);
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

	return spoof_call((t_PresentImpl)Globals::Functions::g_PresentImplementation, pChain, unk1, unk2, unk3, unk4, unk5, unk6);
}




HRESULT Hooks::hk_ResizeBuffer(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
{
	Ulog("%s - ResizeBuffer Called", __FUNCTION__);
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		Globals::Window::BeingResized = true;

		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX11_Shutdown();

		Globals::Window::GameWindow = NULL;
		Globals::Window::pContext = NULL;
		Globals::Window::pDevice = NULL;
		Globals::Window::pChain = NULL;
		Globals::Window::BeingResized = false;
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
	return Globals::Functions::Original_DxgiResizeBuffer(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}
#pragma once

namespace Hooks
{
	UINT64  hk_PresentImplementation(IDXGISwapChain* pChain, void* unk1, void* unk2, void* unk3, void* unk4, void* unk5, void* unk6);
	HRESULT hk_ResizeBuffer(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);

}
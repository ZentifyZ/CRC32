#include "pch.h"
#include "Header/Vmt.h"

inline Internal::VMTHook::VMTHook()
{
}

Internal::VMTHook::VMTHook(void* vmt_addy)
{
	vmt = (void**)vmt_addy;
}


void* Internal::VMTHook::Hook(int index, void* hk)
{
	// Store the index and original function address
	hooked_funcs.insert(std::make_pair(index, vmt[index]));

	// Change the memory's access rights, patch the address to our hook, restore original rights
	DWORD old;
	VirtualProtect(&vmt[index], sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
	vmt[index] = hk;
	VirtualProtect(&vmt[index], sizeof(void*), old, &old);

	return hooked_funcs[index];
}

void Internal::VMTHook::ClearHooks()
{
	for (func_iterator = hooked_funcs.begin(); func_iterator != hooked_funcs.end(); func_iterator++)
	{
		DWORD old;
		VirtualProtect(&vmt[func_iterator->first], sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
		vmt[func_iterator->first] = func_iterator->second;
		VirtualProtect(&vmt[func_iterator->first], sizeof(void*), old, &old);
	}
	hooked_funcs.clear();
	vmt = nullptr;
}

Internal::VMTHook::~VMTHook() {}

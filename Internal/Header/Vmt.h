#pragma once


namespace Internal
{
	class VMTHook
	{
	public:

		void** vmt = nullptr; // Pointer to the VMT, we're using it more as an array of void*

		VMTHook();
		VMTHook(void* vmt); // Hook original VMT by it's address
		~VMTHook(); // Destructor, removes all hooks

		void* Hook(int index, void* hk);
		void ClearHooks();
	private:
		std::map<int, void*>::iterator func_iterator; // Iterator so we can iterate the map below
		std::map<int, void*> hooked_funcs; // std::map which holds the index hooked and the original function's address
	};
}
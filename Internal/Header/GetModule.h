#pragma once

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	WORD LoadCount;
	WORD TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		struct
		{
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};
	union
	{
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};
	_ACTIVATION_CONTEXT* EntryPointActivationContext;
	PVOID PatchInformation;
	LIST_ENTRY ForwarderLinks;
	LIST_ENTRY ServiceTagLinks;
	LIST_ENTRY StaticLinks;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;


namespace Internal
{
	HMODULE cLoadLibA(LPCSTR lpLibName);
	void* HdnGetModuleBase(const char* moduleName);
	void* GetImportB(const char* szDll, const char* szFunc);
	BYTE* GetProcAddressA(HINSTANCE hDll, const char* szFunc);
	HINSTANCE GetModuleHandleExA(HANDLE hProc, const char* szDll);
	PIMAGE_SECTION_HEADER GetImageSection(const uintptr_t image_base, const char* section);
}

typedef HMODULE(WINAPI* pLoadLibA)(IN LPCSTR);

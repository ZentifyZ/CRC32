#include "pch.h"
#include "Header\Scan.h"
#include "Header\GetModule.h"

#ifdef UNICODE
#undef Module32First
#undef Module32Next
#undef MODULEENTRY32
#endif

void* Internal::HdnGetModuleBase(const char* moduleName)
{
	wchar_t wModuleName[100];

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, moduleName, -1, wModuleName, 100);

	#if defined( _WIN64 )  
	#define PEBOffset 0x60  
	#define LdrOffset 0x18  
	#define ListOffset 0x10

	unsigned long long pPeb = __readgsqword(PEBOffset);

	#elif defined( _WIN32 )  
	#define PEBOffset 0x30  
	#define LdrOffset 0x0C  
	#define ListOffset 0x0C  
		unsigned long pPeb = __readfsdword(PEBOffset);
	#endif       
	pPeb = *reinterpret_cast<decltype(pPeb)*>(pPeb + LdrOffset);
	PLDR_DATA_TABLE_ENTRY pModuleList = *reinterpret_cast<PLDR_DATA_TABLE_ENTRY*>(pPeb + ListOffset);
	while (pModuleList->DllBase)
	{
		if (!wcscmp(pModuleList->BaseDllName.Buffer, wModuleName))
			return pModuleList->DllBase;
		pModuleList = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(pModuleList->InLoadOrderLinks.Flink);
	}
	return nullptr;
}


HMODULE Internal::cLoadLibA(LPCSTR lpLibName)
{
	typedef HMODULE(WINAPI* pLoadLibA)(IN LPCSTR);

	pLoadLibA pLoadLibraryA = nullptr;

	if (!pLoadLibraryA)
	{
		constexpr const char NtApi[] = { 'L', 'o', 'a', 'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y','A','\0' };

		constexpr const char ModuleN[] = { 'K', 'E', 'R', 'N', 'E', 'L', 'B', 'A', 'S', 'E','.', 'd', 'l', 'l', '\0' };

		pLoadLibraryA = static_cast<pLoadLibA>(GetImportB(ModuleN, NtApi));
	}

	return pLoadLibraryA(lpLibName);
}


void* Internal::GetImportB(const char* szDll, const char* szFunc)
{
	HINSTANCE hDll = (HINSTANCE)HdnGetModuleBase(szDll);

	if (!hDll)
	{
		hDll = cLoadLibA(szDll);

		if (!hDll)
		{
			return 0;
		}
	}
	else {
	}

	BYTE* pFunc = GetProcAddressA(hDll, szFunc);
	if (!pFunc)
		return 0;

	return pFunc;
}


HINSTANCE Internal::GetModuleHandleExA(HANDLE hProc, const char* szDll)
{
	MODULEENTRY32 ME32{ 0 };
	ME32.dwSize = sizeof(ME32);

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetProcessId(hProc));
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		while (GetLastError() == ERROR_BAD_LENGTH)
		{
			hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetProcessId(hProc));

			if (hSnap != INVALID_HANDLE_VALUE)
				break;
		}
	}

	BOOL bRet = Module32First(hSnap, &ME32);
	while (bRet)
	{
		if (!_stricmp(ME32.szModule, szDll))
			break;
		bRet = Module32Next(hSnap, &ME32);
	}
	CloseHandle(hSnap);

	if (!bRet)
		return NULL;

	return ME32.hModule;
}

PIMAGE_SECTION_HEADER Internal::GetImageSection(const uintptr_t image_base, const char* section)
{
	if (!image_base)
		return 0;

	const PIMAGE_DOS_HEADER pimage_dos_header = (PIMAGE_DOS_HEADER)(image_base);

	if (pimage_dos_header->e_magic != IMAGE_DOS_SIGNATURE)
		return 0;

	const PIMAGE_NT_HEADERS64 pimage_nt_headers = (PIMAGE_NT_HEADERS64)(image_base + pimage_dos_header->e_lfanew);

	if (pimage_nt_headers->Signature != IMAGE_NT_SIGNATURE)
		return 0;

	WORD NumOfSection = pimage_nt_headers->FileHeader.NumberOfSections;

	PIMAGE_SECTION_HEADER Section = IMAGE_FIRST_SECTION(pimage_nt_headers);

	for (WORD i = 0; i < NumOfSection; i++)
	{
		if (strcmp((const char*)Section->Name, section) == 0)
			break;

		Section++;
	}

	return Section;
}


BYTE* Internal::GetProcAddressA(HINSTANCE hDll, const char* szFunc)
{
	if (!hDll)
		return nullptr;

	BYTE* pBase = reinterpret_cast<BYTE*>(hDll);
	auto* pNT = reinterpret_cast<IMAGE_NT_HEADERS*>(pBase + reinterpret_cast<IMAGE_DOS_HEADER*>(pBase)->e_lfanew);
	auto* pDirectory = &pNT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	auto* pExportDir = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(pBase + pDirectory->VirtualAddress);
	auto ExportSize = pDirectory->Size;
	DWORD DirRVA = pDirectory->VirtualAddress;

	if (!ExportSize)
		return nullptr;

	if (reinterpret_cast<UINT_PTR>(szFunc) <= MAXWORD)
	{
		WORD Base = LOWORD(pExportDir->Base - 1);
		WORD Ordinal = LOWORD(szFunc) - Base;
		DWORD FuncRVA = reinterpret_cast<DWORD*>(pBase + pExportDir->AddressOfFunctions)[Ordinal];

		if (FuncRVA >= DirRVA && FuncRVA < DirRVA + ExportSize)
		{
			char pFullExport[MAX_PATH]{ 0 };
			auto Len = strlen(reinterpret_cast<char*>(pBase + FuncRVA));
			if (!Len)
				return nullptr;

			memcpy(pFullExport, reinterpret_cast<char*>(pBase + FuncRVA), Len);
			char* pFuncName = strchr(pFullExport, '.');
			*pFuncName++ = '\0';
			if (*pFuncName == '#')
				pFuncName = reinterpret_cast<char*>(LOWORD(atoi(++pFuncName)));

			HINSTANCE hLib = cLoadLibA(pFullExport);
			if (hLib == reinterpret_cast<HINSTANCE>(hDll) && !_stricmp(pFuncName, szFunc))
			{
				return nullptr;
			}

			return GetProcAddressA(hLib, pFuncName);
		}
	}

	DWORD max = pExportDir->NumberOfNames - 1;
	DWORD min = 0;
	WORD Ordinal = 0;

	while (min <= max)
	{
		DWORD mid = (min + max) >> 1;

		DWORD CurrNameRVA = reinterpret_cast<DWORD*>(pBase + pExportDir->AddressOfNames)[mid];
		char* szName = reinterpret_cast<char*>(pBase + CurrNameRVA);

		int cmp = strcmp(szName, szFunc);
		if (cmp < 0)
			min = mid + 1;
		else if (cmp > 0)
			max = mid - 1;
		else
		{
			Ordinal = reinterpret_cast<WORD*>(pBase + pExportDir->AddressOfNameOrdinals)[mid];
			break;
		}
	}

	if (!Ordinal)
		return nullptr;

	DWORD FuncRVA = reinterpret_cast<DWORD*>(pBase + pExportDir->AddressOfFunctions)[Ordinal];

	if (FuncRVA >= DirRVA && FuncRVA < DirRVA + ExportSize)
	{
		char pFullExport[MAX_PATH]{ 0 };
		auto Len = strlen(reinterpret_cast<char*>(pBase + FuncRVA));
		if (!Len)
			return nullptr;

		memcpy(pFullExport, reinterpret_cast<char*>(pBase + FuncRVA), Len);
		char* pFuncName = strchr(pFullExport, '.');
		*pFuncName++ = '\0';
		if (*pFuncName == '#')
			pFuncName = reinterpret_cast<char*>(LOWORD(atoi(++pFuncName)));

		HINSTANCE hLib = cLoadLibA(pFullExport);
		if (hLib == reinterpret_cast<HINSTANCE>(hDll) && !_stricmp(pFuncName, szFunc))
		{
			return nullptr;
		}

		return GetProcAddressA(hLib, pFuncName);
	}

	return pBase + FuncRVA;
}

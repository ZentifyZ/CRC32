#include "pch.h"
#include "Scan.h"
#include "Detour.h"
#include "GetModule.h"
#include "Header/AAnticheat.h"


BOOL EAC::SecureInternalWriteProcessMemory(LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize)
{
	ULONG old;
	SIZE_T Size = nSize;
	LPVOID BaseAddress = lpBaseAddress;

	BOOLEAN status = EAC::SecureInternalVirtualProtect(lpBaseAddress, nSize, PAGE_EXECUTE_READWRITE, &old);

	if (!status)
	{
		Ulog("%s - SecureInternalVirtualProtect failed", __FUNCTION__);
		return false;
	}

	memcpy(BaseAddress, lpBuffer, Size);

	status = EAC::SecureInternalVirtualProtect(lpBaseAddress, nSize, old, &old);

	if (!status)
	{
		Ulog("%s - SecureInternalVirtualProtect failed", __FUNCTION__);
		return false;
	}

	return true;
}

BOOL EAC::SecureInternalVirtualProtect(IN OUT PVOID BaseAddress, IN OUT SIZE_T NumberOfBytesToProtect, IN ULONG NewAccessProtection, OUT PULONG OldAccessProtection)
{
	LONG Status = import_NtProtectVirtualMemory(GetCurrentProcess(), &BaseAddress, &NumberOfBytesToProtect, NewAccessProtection, OldAccessProtection);

	if (Status != 0)
	{
		Ulog("%s - import_NtProtectVirtualMemory failed with status: %lx", __FUNCTION__, Status);
		return false;
	}

	Status = import_NtFlushInstructionCache(GetCurrentProcess(), BaseAddress, NumberOfBytesToProtect);

	if (Status != 0)
	{
		Ulog("%s - import_NtFlushInstructionCache failed with status: %lx", __FUNCTION__, Status);
		return false;
	}

	return true;
}

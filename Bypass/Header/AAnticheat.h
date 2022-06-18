#pragma once


namespace EAC
{
	BOOL SecureInternalWriteProcessMemory(LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize);
	BOOL SecureInternalVirtualProtect(IN OUT PVOID BaseAddress, IN OUT SIZE_T NumberOfBytesToProtect, IN ULONG NewAccessProtection, OUT PULONG OldAccessProtection);
};

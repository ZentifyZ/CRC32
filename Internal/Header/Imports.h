#pragma once

namespace Internal
{
	// Network Operations
	typedef SOCKET(WINAPI* t_Socket)(int af, int type, int protocol);
	typedef unsigned short (WINAPI* t_htons)(unsigned short hostshort);
	typedef int (WINAPI* t_Send)(SOCKET s, const char* buf, int len, int flags);
	typedef int (WINAPI* t_WSAEnumNetworkEvents)(SOCKET s, HANDLE hEventObject, LPWSANETWORKEVENTS lpNetworkEvents);
	typedef int (WINAPI* t_WSAEventSelect)(SOCKET s, HANDLE hEventObject, int lNetworkEvents);
	typedef int (WINAPI* t_WSAStartup)(WORD wVersionRequested, LPWSADATA lpWSAData);
	typedef int (WINAPI* t_getaddrinfo)(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA* pHints, PADDRINFOA* ppResult);
	typedef int (WINAPI* t_WSAGetLastError)(void);
	typedef int (WINAPI* t_closesocket)(SOCKET s);
	typedef int (WINAPI* t_connect)(SOCKET s, const struct sockaddr* name, int namelen);
	typedef int (WINAPI* t_recv)(SOCKET s, char* buf, int len, int flags);
	typedef int (WINAPI* t_WSACleanup)(void);
	typedef SHORT (WINAPI* t_NtUserGetAsyncKeyState)(int key);

	// Memory Operations
	typedef LONG (WINAPI* t_NtProtectVirtualMemory)(IN HANDLE ProcessHandle, IN OUT PVOID* BaseAddress, IN OUT SIZE_T* NumberOfBytesToProtect, IN ULONG NewAccessProtection, OUT PULONG OldAccessProtection);
	typedef LONG (WINAPI* t_NtQuerySystemInformation)(IN int SystemInformationClass, OUT PVOID SystemInformation, IN ULONG SystemInformationLength, OUT PULONG ReturnLength OPTIONAL);
	typedef LONG (WINAPI* t_NtFlushInstructionCache)(IN HANDLE ProcessHandle, IN PVOID BaseAddress, IN SIZE_T FlushSize);
	typedef BOOL (WINAPI* t_WriteProcessMemory)(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten);
	typedef BOOL (WINAPI* t_NtQueryVirtualMemory)(HANDLE hProcess, LPCVOID lpAddress, ULONGLONG MemoryClass, UINT_PTR lpBuffer, SIZE_T dwLength, PSIZE_T ReturnLength);
	typedef BOOL (WINAPI* t_NtAllocateVirtualMemory)(HANDLE handle, LPVOID* lpAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect);

	bool DynamicImportWinAPIs();
};	

// Network functions
inline Internal::t_Send import_send = NULL;
inline Internal::t_Socket import_socket = NULL;
inline Internal::t_htons import_htons = NULL;
inline Internal::t_WSAEnumNetworkEvents import_WSAEnumNetworkEvents = NULL;
inline Internal::t_WSAEventSelect import_WSAEventSelect = NULL;
inline Internal::t_WSAStartup import_WSAStartup = NULL;
inline Internal::t_getaddrinfo import_getaddrinfo = NULL;
inline Internal::t_WSAGetLastError import_WSAGetLastError = NULL;
inline Internal::t_closesocket import_closesocket = NULL;
inline Internal::t_connect import_connect = NULL;
inline Internal::t_recv import_recv = NULL;
inline Internal::t_WSACleanup import_WSACleanup = NULL;

// Memory functions
inline Internal::t_NtProtectVirtualMemory import_NtProtectVirtualMemory = NULL;
inline Internal::t_NtQuerySystemInformation import_NtQuerySystemInformation = NULL;
inline Internal::t_NtFlushInstructionCache import_NtFlushInstructionCache = NULL;
inline Internal::t_WriteProcessMemory import_WriteProcessMemory = NULL;
inline Internal::t_NtQueryVirtualMemory import_NtQueryVirtualMemory = NULL;
inline Internal::t_NtAllocateVirtualMemory import_NtAllocateVirtualMemory = NULL;

// Input functions
inline Internal::t_NtUserGetAsyncKeyState import_NtUserGetAsyncKeyState = NULL;

#define WIN32_LEAN_AND_MEAN

#include "pch.h"
#include "GetModule.h"


bool Internal::DynamicImportWinAPIs()
{
	// Networking Functions Resolve
	import_send = (t_Send)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("send"));
	import_htons = (t_htons)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("htons"));
	import_socket = (t_Socket)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("socket"));
	import_WSAEnumNetworkEvents = (t_WSAEnumNetworkEvents)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("WSAEnumNetworkEvents"));
	import_WSAEventSelect = (t_WSAEventSelect)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("WSAEventSelect"));;
	import_WSAStartup = (t_WSAStartup)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_(("WSAStartup")));;
	import_getaddrinfo = (t_getaddrinfo)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("getaddrinfo"));;
	import_WSAGetLastError = (t_WSAGetLastError)Internal::GetImportB("WS2_32.dll", xorstr_("WSAGetLastError"));;
	import_closesocket = (t_closesocket)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("closesocket"));;
	import_connect = (t_connect)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("connect"));;
	import_recv = (t_recv)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("recv"));;
	import_WSACleanup = (t_WSACleanup)Internal::GetImportB(xorstr_("WS2_32.dll"), xorstr_("WSACleanup"));;

	if (!import_send || !import_htons || !import_socket || !import_WSAEnumNetworkEvents || !import_WSAEventSelect ||
		!import_WSAStartup || !import_getaddrinfo || !import_WSAGetLastError || !import_closesocket || !import_connect ||
		!import_recv || !import_WSACleanup)
	{
		Ulog("%s - Failed to dynamically resolve network APIs.", __FUNCTION__);
		return false;
	}

	// Memory operations functions resolve
	import_NtProtectVirtualMemory = (t_NtProtectVirtualMemory)Internal::GetImportB(xorstr_("ntdll.dll"), xorstr_("NtProtectVirtualMemory"));
	import_NtQuerySystemInformation = (t_NtQuerySystemInformation)Internal::GetImportB(xorstr_("ntdll.dll"), xorstr_("NtQuerySystemInformation"));
	import_NtFlushInstructionCache = (t_NtFlushInstructionCache)Internal::GetImportB(xorstr_("ntdll.dll"), xorstr_("NtFlushInstructionCache"));
	import_NtQueryVirtualMemory = (t_NtQueryVirtualMemory)Internal::GetImportB(xorstr_("ntdll.dll"), xorstr_("NtQueryVirtualMemory"));
	import_NtAllocateVirtualMemory = (t_NtAllocateVirtualMemory)Internal::GetImportB(xorstr_("ntdll.dll"), xorstr_("NtAllocateVirtualMemory"));

	// kernel32
	import_WriteProcessMemory = (t_WriteProcessMemory)Internal::GetImportB(xorstr_("kernelbase.dll"), xorstr_("WriteProcessMemory"));

	if (!import_NtProtectVirtualMemory || !import_NtQuerySystemInformation || !import_NtFlushInstructionCache || 
		!import_WriteProcessMemory || !import_NtQueryVirtualMemory || !import_NtAllocateVirtualMemory)
	{
		Ulog("%s - Failed to dynamically resolve memory APIs.", __FUNCTION__);
		return false;
	}

	// Input functions
	import_NtUserGetAsyncKeyState = (t_NtUserGetAsyncKeyState)Internal::GetImportB(xorstr_("win32u.dll"), xorstr_("NtUserGetAsyncKeyState"));

	if (!import_NtUserGetAsyncKeyState)
	{
		Ulog("%s - Failed to dynamically resolve input APIs.", __FUNCTION__);
		return false;
	}


	return true;
}
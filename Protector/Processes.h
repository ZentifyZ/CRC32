#pragma once

typedef struct _SYSTEM_PROCESS_INFO
{
    ULONG                   NextEntryOffset;
    ULONG                   NumberOfThreads;
    LARGE_INTEGER           Reserved[3];
    LARGE_INTEGER           CreateTime;
    LARGE_INTEGER           UserTime;
    LARGE_INTEGER           KernelTime;
    UNICODE_STRING          ImageName;
    ULONG                   BasePriority;
    HANDLE                  ProcessId;
    HANDLE                  InheritedFromProcessId;
}SYSTEM_PROCESS_INFO, * PSYSTEM_PROCESS_INFO;


#define UNICREATE(string) {sizeof(string) - 2, sizeof(string), string}

inline PUSHORT NlsUnicodeUpcaseTable = NULL;

__forceinline WCHAR NTAPI RtlpUpcaseUnicodeChar402(IN WCHAR Source)
{
    USHORT Offset;

    if (Source < 'a')
        return Source;

    if (Source <= 'z')
        return (Source - ('a' - 'A'));

    Offset = ((USHORT)Source >> 8) & 0xFF;
    Offset = NlsUnicodeUpcaseTable[Offset];

    Offset += ((USHORT)Source >> 4) & 0xF;
    Offset = NlsUnicodeUpcaseTable[Offset];

    Offset += ((USHORT)Source & 0xF);
    Offset = NlsUnicodeUpcaseTable[Offset];

    return Source + (SHORT)Offset;
}

__forceinline const LONG RTLCompareUnicodeString402(PCUNICODE_STRING s1, PCUNICODE_STRING s2)
{
    unsigned int len;
    LONG ret = 0;
    LPCWSTR p1, p2;

    len = min(s1->Length, s2->Length) / sizeof(WCHAR);
    p1 = s1->Buffer;
    p2 = s2->Buffer;

    while (!ret && len--) ret = RtlpUpcaseUnicodeChar402(*p1++) - RtlpUpcaseUnicodeChar402(*p2++);


    if (!ret) ret = s1->Length - s2->Length;

    return ret;
}


/*
    Check for tools like IDA, Reclass, etc

    Return: 0 if everything is good, 1 if found bad processes, 2+ for error codes such as Failed SYSCALL
*/

__forceinline const int FindBadProcesses()
{
    NTSTATUS status;
    PVOID buffer = NULL;
    PSYSTEM_PROCESS_INFO spi;
    SIZE_T memSize = 1024 * 1024;

    std::vector<UNICODE_STRING> badProcesses = { UNICREATE(L"ida64.exe"),  UNICREATE(L"ida.exe"), UNICREATE(L"cheatengine-x86_64.exe"), UNICREATE(L"cheatengine-i386.exe"), UNICREATE(L"x64dbg.exe"),
    UNICREATE(L"x32dbg.exe"), UNICREATE(L"x96dbg.exe"), UNICREATE(L"ReClass.NET.exe"), UNICREATE(L"ReClass.exe"), UNICREATE(L"tcpview.exe"), UNICREATE(L"ollydbg.exe"), UNICREATE(L"ProcessHacker.exe"),
    UNICREATE(L"filemon.exe"), UNICREATE(L"procmon.exe"), UNICREATE(L"procmon64.exe"), UNICREATE(L"regmon.exe"), UNICREATE(L"de4dot.exe"), UNICREATE(L"dnSpy.exe"), UNICREATE(L"procexp.exe"), UNICREATE(L"procexp64.exe"),
    UNICREATE(L"idaq.exe"), UNICREATE(L"idaq64.exe"), UNICREATE(L"ImmunityDebugger.exe"), UNICREATE(L"Wireshark.exe"), UNICREATE(L"dumpcap.exe"), UNICREATE(L"HookExplorer.exe"), UNICREATE(L"ImportREC.exe"), UNICREATE(L"PETools.exe"),
    UNICREATE(L"LordPE.exe"), UNICREATE(L"dotPeek.exe"), UNICREATE(L"windbg.exe"), UNICREATE(L"sniff_hit.exe"), UNICREATE(L"fiddler.exe"), UNICREATE(L"proc_analyzer.exe"), UNICREATE(L"CFF Explorer.exe"), UNICREATE(L"apimonitor-x86.exe"), UNICREATE(L"apimonitor-x64.exe"),
    UNICREATE(L"PEiD.exe.exe") , UNICREATE(L"radare2.exe") , UNICREATE(L"hopper.exe") };

    buffer = new char[memSize];

    if (!buffer)
        return FAILED_SYSCALL;

    spi = reinterpret_cast<PSYSTEM_PROCESS_INFO>(buffer);
    status = import_NtQuerySystemInformation(SystemProcessInformation, spi, memSize, NULL);

    if (!NT_SUCCESS(status))
        return FAILED_SYSCALL;

    while (spi->NextEntryOffset) // Loop over the list until we reach the last entry.
    {
#ifndef P402DISTRIBUTE
        printf("Process name: %ws | Process ID: %d\n", spi->ImageName.Buffer, spi->ProcessId); // Display process information.
#endif // !P402DISTRIBUTE

        for (auto process : badProcesses)
        {
            if (RTLCompareUnicodeString402(&spi->ImageName, &process) == 0)
            {
                printf("[!] Bad process found %ws.\n", spi->ImageName.Buffer);

                delete[] buffer; buffer = 0;

                return TRUE; // Found bad process

            }
        }

        spi = (PSYSTEM_PROCESS_INFO)((LPBYTE)spi + spi->NextEntryOffset); // Calculate the address of the next entry.
    }

    delete[] buffer; buffer = 0;

    if (!NT_SUCCESS(status))
        return FAILED_SYSCALL;

    return FALSE;
}


__forceinline DWORD GetWindowsVersion()
{
    static const wchar_t kernel32[] = L"\\kernel32.dll";
    wchar_t* path = NULL;
    void* ver = NULL, * block;
    UINT n;
    BOOL r;
    DWORD versz, blocksz;
    VS_FIXEDFILEINFO* vinfo;

    path = (wchar_t*)malloc(sizeof(*path) * MAX_PATH);
    if (!path)
        abort();

    n = GetSystemDirectoryW(path, MAX_PATH);
    if (n >= MAX_PATH || n == 0 ||
        n > MAX_PATH - sizeof(kernel32) / sizeof(*kernel32))
        abort();
    memcpy(path + n, kernel32, sizeof(kernel32));

    versz = GetFileVersionInfoSizeW(path, NULL);
    if (versz == 0)
        abort();
    ver = malloc(versz);
    if (!ver)
        abort();
    r = GetFileVersionInfoW(path, 0, versz, ver);
    if (!r)
        abort();
    r = VerQueryValueW(ver, L"\\", &block, (PUINT)&blocksz);
    if (!r || blocksz < sizeof(VS_FIXEDFILEINFO))
        abort();
    vinfo = (VS_FIXEDFILEINFO*)block;

    if ((int)HIWORD(vinfo->dwProductVersionMS) != 10)
        abort();

    return HIWORD(vinfo->dwFileVersionLS);
}

/*
    Purpose: EnumWindow Syscall callback to populate window list.

*/
__forceinline BOOL CALLBACK EnumWindows402Callback(HWND hwnd, LPARAM lParam)
{
    const DWORD TITLE_SIZE = 4096;
    WCHAR windowTitle[TITLE_SIZE];

    GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);

    int length = ::GetWindowTextLengthW(hwnd);

    std::wstring title(&windowTitle[0]);
    if (length == 0) {
        return TRUE;
    }
    std::vector<std::wstring>& titles =
        *reinterpret_cast<std::vector<std::wstring>*>(lParam);

    titles.push_back(title);
}


/*
    Check for tools like IDA, Reclass, etc through Windows name

    Return: 0 if everything is good, 1 if found bad processes, 2+ for error codes such as Failed SYSCALL
*/

__forceinline const bool FindBadWindows()
{
    std::vector<std::wstring> titles; titles.reserve(4096);

    BOOL Status = EnumWindows(EnumWindows402Callback, reinterpret_cast<LPARAM>(&titles));

    if (!Status)
    {
        titles.clear();
        return FAILED_SYSCALL;
    }

    if (titles.size() < 10)
    {
        titles.clear();
        return WINDOW_LIST_EMPTY;
    }

    std::vector<std::wstring> badWindowsTitles = { L"ida", L"Cheat Engine", L"x64dbg", L"x32dbg", L"x96dbg", L"Reclass", L"TCPView", L"Sysinternals", L"OllyDbg", L"Process Hacker", L"File Monitor", L"Process Monitor", L"Registry Monitor", L"de4dot", L"dnSpy",
    L"Process Explorer", L"Immunity Debugger", L"Wireshark", L"Hook Explorer", L"MackT", L"REConstructor", L"PE Tools", L"uinc.ru", L"LordPE", L"dotPeek", L"WinDbg", L"Fiddler", L"CFF Explorer", L"API Monitor", L"PEiD", L"Cerbero Suite" };

    auto search_substring = [](const std::wstring& strHaystack, const std::wstring& strNeedle) -> bool
    {
        auto it = std::search(
            strHaystack.begin(), strHaystack.end(),
            strNeedle.begin(), strNeedle.end(),
            [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
        );
        return (it != strHaystack.end());
    };
    for (auto title : titles)
    {
        for (auto badWindow : badWindowsTitles)
        {
            if (search_substring(title, badWindow))
            {
                printf("[|] Bad process found %S. You might be temporary banned :) Might wanna restart?\n", title.data());
                titles.clear();
                return BAD_WINDOWS_FOUND;
            }
        }
    }
    titles.clear();

    return FALSE;
}

/*
    Return:
        FALSE if no bad windows and process is found aka "Good, let's keep going"
        TRUE if we found any bad things, if this return TRUE - do not run and just close out.
*/

BOOL ARE_BAD_TOOLS_RUNNING();

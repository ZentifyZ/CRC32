#include "pch.h"
#include "Header\Scan.h"

bool INT_ComparePattern(char* szSource, const char* szPattern, const char* szMask)
{
    ULONG ExceptionCode = 0;
    PEXCEPTION_POINTERS ExceptionPointers = 0;
    __try
    {
        for (; *szMask; ++szSource, ++szPattern, ++szMask)
            if (*szMask == 'x' && *szSource != *szPattern)
                return false;
        return true;
    }
    __except (
        ExceptionCode = GetExceptionCode(),
        ExceptionPointers = GetExceptionInformation(),
        EXCEPTION_EXECUTE_HANDLER
        ) {
        if (ExceptionPointers)
        {
            Ulog("Exception (%lx) caught in %s @ (%p) with Address (%llx)",
                ExceptionCode, __FUNCTION__,
                ExceptionPointers->ExceptionRecord->ExceptionAddress,
                szSource
            );
        }
    } return false;
}

char* INT_PatternScan(char* pData, UINT_PTR RegionSize, const char* szPattern, const char* szMask, int Len)
{
    for (UINT i = 0; i != RegionSize - Len; ++i, ++pData)
        if (INT_ComparePattern(pData, szPattern, szMask))
            return pData;
    return nullptr;
}

UINT_PTR Internal::FindPattern(uintptr_t base, const PBYTE Pattern, const char* Mask) {
    PBYTE Start = (PBYTE)base;
    PIMAGE_NT_HEADERS NTHead = (PIMAGE_NT_HEADERS)(Start + ((PIMAGE_DOS_HEADER)Start)->e_lfanew);
    DWORD Len = NTHead->OptionalHeader.SizeOfImage;

    for (PBYTE region_it = Start; region_it < (Start + Len); ++region_it) {
        if (*region_it == *Pattern) {
            bool found = true;
            const unsigned char* pattern_it = Pattern, * mask_it = (const PBYTE)Mask, * memory_it = region_it;
            for (; *mask_it && (memory_it < (Start + Len)); ++mask_it, ++pattern_it, ++memory_it) {
                if (*mask_it != 'x') continue;
                if (*memory_it != *pattern_it) {
                    found = false;
                    break;
                }
            }

            if (found)
                return (uintptr_t)region_it;
        }
    }

    return 0;
}

UINT_PTR Internal::FindPatternIDA(UINT_PTR dwAddress, UINT_PTR dwLen, CHAR* bPattern, BOOL Unsafe)
{
    ULONG ExceptionCode = 0;
    PEXCEPTION_POINTERS ExceptionPointers = 0;
    __try
    {
        if (!dwAddress || !dwLen || !bPattern)
            return 0;
        auto SwitchHex = [](CHAR c) -> CHAR
        {
            switch (c)
            {
            case '0': return 0;
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case '4': return 4;
            case '5': return 5;
            case '6': return 6;
            case '7': return 7;
            case '8': return 8;
            case '9': return 9;
            case 'a': return 10;
            case 'b': return 11;
            case 'c': return 12;
            case 'd': return 13;
            case 'e': return 14;
            case 'f': return 15;

            case 'A': return 10;
            case 'B': return 11;
            case 'C': return 12;
            case 'D': return 13;
            case 'E': return 14;
            case 'F': return 15;
            default:
                break;
            }
        };

        auto GenerateMask = [SwitchHex](IN CHAR* Pattern, OUT CHAR* NewPattern, OUT CHAR* newMask) -> VOID
        {
            CHAR bMask[100] = { 0 };
            CHAR bPattern[100] = { 0 };
            CHAR bWildCardPosition[100] = { 0 };

            INT i = 0, length = 0;
            while (Pattern[i])
            {
                if (Pattern[i] != ' ') // Removing all white spaces
                    bPattern[length++] = Pattern[i];
                i++;
            } bPattern[length] = '\0';


            UINT64 l = 0;
            for (UINT64 k = 0; k < length;)
            {
                if (bPattern[k] == '?')
                {
                    k++;
                    bWildCardPosition[l] = true;
                    bPattern[l++] = '\xCC';
                    continue;
                }

                if (!bPattern[k])
                    break;

                BYTE b1 = SwitchHex(bPattern[k++]);
                BYTE b2 = SwitchHex(bPattern[k++]);
                BYTE b = (b1 << 4) | b2;

                bPattern[l++] = b;
            }
            bPattern[l] = '\0';

            for (size_t m = 0; m < l; m++)
            {
                if (bWildCardPosition[m]) // Replacing ? with \xCC byte
                {
                    bMask[m] = '?';
                }
                else
                {
                    bMask[m] = 'x';
                }
            }

            RtlCopyMemory(newMask, bMask, l);
            RtlCopyMemory(NewPattern, bPattern, l);
        };

        CHAR newMask[100] = { 0 };
        UCHAR newPattern[100] = { 0 };
        GenerateMask(bPattern, (CHAR*)newPattern, newMask);

        if (Unsafe) return Internal::PatternScanUnsafe<UINT_PTR>(dwAddress, dwLen, (const char*)newPattern, newMask);
        else return Internal::PatternScan<UINT_PTR>(dwAddress, dwLen, (const char*)newPattern, newMask);
    }
    __except (
        ExceptionCode = GetExceptionCode(),
        ExceptionPointers = GetExceptionInformation(),
        EXCEPTION_EXECUTE_HANDLER
        ) {
        if (ExceptionPointers)
        {
            Ulog("Exception (%lx) caught in %s @ (%p) with Address (%llx) and Len (%llx)",
                ExceptionCode, __FUNCTION__,
                ExceptionPointers->ExceptionRecord->ExceptionAddress,
                dwAddress, dwLen
            );
        }
    } return 0;
}



template <typename T>
T Internal::PatternScan(T pStart, UINT_PTR RegionSize, const char* szPattern, const char* szMask)
{
    char* pCurrent = (char*)pStart;
    auto Len = lstrlenA(szMask);

    while (pCurrent <= (char*)pStart + RegionSize - Len)
    {
        MEMORY_BASIC_INFORMATION MBI{ 0 };

        SIZE_T ReturnLength;
        if ((import_NtQueryVirtualMemory(GetCurrentProcess(), pCurrent, 0, (UINT_PTR)&MBI, sizeof MBI, &ReturnLength) & 0x80000000) != 0)
            return 0;

        if (MBI.State == MEM_COMMIT && !(MBI.Protect & PAGE_NOACCESS))
        {
            if (pCurrent + MBI.RegionSize > (char*)pStart + RegionSize - Len)
                MBI.RegionSize = (char*)pStart + RegionSize - pCurrent + Len;

            char* Ret = INT_PatternScan(pCurrent, MBI.RegionSize, szPattern, szMask, Len);

            if (Ret)
            {
                return (T)Ret;
            }

        }
        pCurrent += MBI.RegionSize;
    }
    return 0;
}

template <typename T>
T Internal::PatternScanUnsafe(T pStart, UINT_PTR RegionSize, const char* szPattern, const char* szMask)
{
    char* pCurrent = (char*)pStart;
    auto Len = lstrlenA(szMask);

    if (Len > RegionSize)
        return 0;

    return (T)INT_PatternScan(pCurrent, RegionSize, szPattern, szMask, Len);
}


uintptr_t Internal::scan_for_ptr(uintptr_t dwAddress, uintptr_t dwLen, uintptr_t dwOffset, uintptr_t i_length, uintptr_t operand_size, char* bPattern, char* bMask, char* pName)
{
    uintptr_t bFound = Internal::PatternScan(dwAddress, dwLen, bPattern, bMask);

    if (!bFound) { return 0; }

    uintptr_t offset_value = bFound + dwOffset + operand_size;

    INT32 delta = *(INT32*)offset_value;

    return i_length + delta + bFound;
}

uintptr_t Internal::PointerScannerIDA(uintptr_t dwAddress, uintptr_t dwLen, uintptr_t dwOffset, uintptr_t i_length, uintptr_t operand_size, char* bPattern, char* pName)
{
    uintptr_t bFound = Internal::FindPatternIDA(dwAddress, dwLen, bPattern);

    if (!bFound) { return 0; }

    uintptr_t offset_value = bFound + dwOffset + operand_size;

    INT32 delta = *(INT32*)offset_value;

    return i_length + delta + bFound;
}


char* Internal::ptr_offset_Scanner(char* pBase, UINT_PTR RegionSize, const char* szPattern, uintptr_t i_offset,
    uintptr_t i_length, uintptr_t instruction_before_offset, const char* szMask)
{
    char* initial_addr = Internal::PatternScan(pBase, RegionSize, szPattern, szMask);
    if (!initial_addr)
    {
        return nullptr;
    }

    char* offset_read = nullptr;
    char* second_addr = initial_addr + i_offset + instruction_before_offset;

    memcpy(&offset_read, second_addr, i_length - instruction_before_offset);

    offset_read = i_length + initial_addr + i_offset + (int)offset_read;


    if (offset_read)
        return offset_read;

    return nullptr;
}

INT32 Internal::OffsetScan(__int64 Base, __int64 RegionSize, int InstructionOffset, int InstructionFullLength, int OpcodeSize, char* bPattern, char* bMask)
{
    auto OffsetAddress = Internal::PatternScan(Base, RegionSize, bPattern, bMask);

    if (!OffsetAddress) return 0;

    return *(INT32*)(OffsetAddress + InstructionOffset + OpcodeSize);
}

INT32 Internal::OffsetScanIDA(__int64 Base, __int64 RegionSize, int InstructionOffset, int InstructionFullLength, int OpcodeSize, char* bPattern)
{
    auto OffsetAddress = Internal::FindPatternIDA(Base, RegionSize, bPattern);

    if (!OffsetAddress) return 0;

    return *(INT32*)(OffsetAddress + InstructionOffset + OpcodeSize);
}

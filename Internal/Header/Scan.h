#pragma once

namespace Internal
{
	template <typename T>
	T PatternScan(T pStart, UINT_PTR RegionSize, const char* szPattern, const char* szMask);

	template <typename T>
	T PatternScanUnsafe(T pStart, UINT_PTR RegionSize, const char* szPattern, const char* szMask);

	//deprecated
	uintptr_t scan_for_ptr(uintptr_t dwAddress, uintptr_t dwLen, uintptr_t dwOffset, uintptr_t i_length, uintptr_t operand_size, char* bPattern, char* bMask, char* pName);

	uintptr_t PointerScannerIDA(uintptr_t dwAddress, uintptr_t dwLen, uintptr_t dwOffset, uintptr_t i_length, uintptr_t operand_size, char* bPattern, char* pName);

	char* ptr_offset_Scanner(char* pBase, UINT_PTR RegionSize, const char* szPattern, uintptr_t i_offset,
		uintptr_t i_length, uintptr_t instruction_before_offset, const char* szMask);

	INT32 OffsetScan(__int64 Base, __int64 RegionSize, int InstructionOffset, int InstructionFullLength, int OpcodeSize, char* bPattern, char* bMask);
	INT32 OffsetScanIDA(__int64 Base, __int64 RegionSize, int InstructionOffset, int InstructionFullLength, int OpcodeSize, char* bPattern);

	UINT_PTR FindPattern(uintptr_t base, const PBYTE Pattern, const char* Mask);
	UINT_PTR FindPatternIDA(UINT_PTR dwAddress, UINT_PTR dwLen, CHAR* bPattern, BOOL Unsafe = false);
}
template <class T>
UINT_PTR ScanMemory(char* pData, UINT_PTR RegionSize, T Val, UINT_PTR* pOut, UINT_PTR MaxCount, BYTE Alignment, char* OriginalBase = nullptr)
{
	UINT_PTR Count = 0;
	for (ULONG i = 0; i < (RegionSize - sizeof(T)) && Count < MaxCount; i += Alignment, pData += Alignment)
		if (*reinterpret_cast<T*>(pData) == Val)
		{
			if (OriginalBase)
				pOut[Count] = reinterpret_cast<UINT_PTR>(OriginalBase + i);
			else
				pOut[Count] = reinterpret_cast<UINT_PTR>(pData);
			Count++;
		}
	return Count;
}

#pragma once
#include <windows.h>

namespace Memory
{
    void* patternScan(char* base, size_t size, const char* pattern, const char* mask);

    void* patternScanEx(HANDLE hPRocess, uintptr_t begin, uintptr_t end, const char* pattern, const char* mask);

    void* patternScanExModule(HANDLE hProcess, DWORD processID, const wchar_t* module, const char* pattern, const char* mask);
} // namespace Memory;

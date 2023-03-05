#pragma once
#include <windows.h>

class Memory
{

public:
    Memory() = default;

    static DWORD getProcessID(const char *procname);
    static uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

};


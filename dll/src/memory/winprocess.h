#pragma once

#include <windows.h>
#include <tlhelp32.h>

namespace Memory
{
    DWORD getProcessID(const wchar_t* procname); // aka GetProc
    uintptr_t getModuleBaseAddress(DWORD procId, const wchar_t* modname); // aka GetModuleBaseAddress
    MODULEENTRY32 getModuleEntry(DWORD dwProcID, const wchar_t* moduleName); // aka GetModule
} // namespace Memory;

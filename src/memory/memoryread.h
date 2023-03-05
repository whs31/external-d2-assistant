#pragma once

#include <vector>
#include <windows.h>
#include <TlHelp32.h>

DWORD getProcessID(const char *procname);
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

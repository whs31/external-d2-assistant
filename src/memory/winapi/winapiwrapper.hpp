#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

namespace WinAPIExtended {

    HMODULE WINAPI getExternalModuleHandle(HANDLE hProcess, LPCSTR lpModuleName);

    FARPROC WINAPI getExternalProcAddress (HANDLE hProcess, HMODULE hModule, LPCSTR lpProcName, UINT Ordinal = 0, BOOL useOrdinal = FALSE);

} /// namespace WinAPIExtended;

#include "winprocess.h"
#include <string>

using std::string;
using std::wstring;

DWORD GetProcId(const wchar_t* procName)
{
    wstring proc_name(procName);
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                string sz_exe_file(procEntry.szExeFile);
                wstring wsz_exe_file(sz_exe_file.begin(), sz_exe_file.end());
                if(not wsz_exe_file.compare(proc_name))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));

        }
    }
    CloseHandle(hSnap);
    return procId;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    wstring mod_name(modName);
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                string sz_module(modEntry.szModule);
                wstring wsz_module(sz_module.begin(), sz_module.end());
                if (not wsz_module.compare(mod_name))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

//Get ModuleEntry from module name, using toolhelp32snapshot
MODULEENTRY32 GetModule(DWORD dwProcID, const wchar_t* moduleName)
{
    wstring proc_name(moduleName);
    MODULEENTRY32 modEntry = { 0 };

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 curr = { 0 };

        curr.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &curr))
        {
            do
            {
                string sz_module(curr.szModule);
                wstring wsz_module(sz_module.begin(), sz_module.end());
                if (not wsz_module.compare(proc_name))
                {
                    modEntry = curr;
                    break;
                }
            } while (Module32Next(hSnapshot, &curr));
        }
        CloseHandle(hSnapshot);
    }
    return modEntry;
}

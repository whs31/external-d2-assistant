#include "memorytools.hpp"

#include <TlHelp32.h>
#include <QDebug>
#include <QtGlobal>
#include <fstream>
#include <string>
#include <regex>

using std::string;

bool Memory::linkToProcess(const char* name)
{
    Memory::base::processID = Memory::getProcessID(name);
    Memory::base::processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, Memory::base::processID);
    if(not Memory::base::processID)
    {
        qCritical() << "[MEMORY] Process not found. Is process launched?";
        return false;
    }
    else
        qInfo().nospace() << "[MEMORY] Linked to process with ID: " << Memory::base::processID << ", HANDLE: " << Memory::base::processHandle;

    Memory::base::clientDll = Memory::getModuleBaseAddress(Memory::base::processID, "client.dll");
    Memory::base::serverDll = Memory::getModuleBaseAddress(Memory::base::processID, "server.dll");
    if(Memory::base::clientDll * Memory::base::serverDll)
        qDebug().nospace() << "[MEMORY] Entry points found. " << Qt::hex << "client.dll: 0x" << Memory::base::clientDll << ", server.dll: 0x" << Memory::base::serverDll << Qt::dec;
    else
    {
        qCritical() << "[MEMORY] Entry point not found.";
        return false;
    }
    return true;
}

uint32_t Memory::getProcessID(const char *procname)
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe;
    int pid = 0;
    BOOL hResult;

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) return 0;
    pe.dwSize = sizeof(PROCESSENTRY32);
    hResult = Process32First(hSnapshot, &pe);
    while (hResult) {
        #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        if (strstr(procname, pe.szExeFile)) {
        #elif QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        if (QString(procname) == QString::fromWCharArray(pe.szExeFile)) {
        #endif
            pid = pe.th32ProcessID;
            break;
        }
        hResult = Process32Next(hSnapshot, &pe);
    }

    CloseHandle(hSnapshot);
    return pid;
}

uintptr_t Memory::getModuleBaseAddress(uint32_t procId, const char* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
                if (strstr(modName, modEntry.szModule)) {
                #elif QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
                if (QString(modName) == QString::fromWCharArray(modEntry.szModule)) {
                #endif
                    CloseHandle(hSnap);
                    return (uintptr_t)modEntry.modBaseAddr;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

string Memory::registry::getGamePathFromRegistry()
{
    HKEY hkey {};
    if(int _error = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Classes\\dota2\\Shell\\Open\\Command", 0, KEY_QUERY_VALUE, &hkey) != ERROR_SUCCESS)
    {
        RegCloseKey(hkey);
        qCritical() << "[MEMORY] Failed to open Registry key with code" << _error;
        return string();
    }

    char dota_path_reg[MAX_PATH]{};
    dota_path_reg[0] = '"';
    DWORD dota_path_size = sizeof(dota_path_reg) - sizeof(char);

    if (int _error = RegQueryValueExA(hkey, nullptr, nullptr, nullptr, (LPBYTE)(dota_path_reg + 1), &dota_path_size) != ERROR_SUCCESS) {
        qCritical() << "[MEMORY] Failed at Regustry Query with code" << _error;
            RegCloseKey(hkey);
        return string();
    }

    RegCloseKey(hkey);

    return string(dota_path_reg);
}

string Memory::registry::getGamePath()
{
    std::string dota_path = getGamePathFromRegistry();
    if(dota_path.empty()) {
        return string();
    }

    std::regex rgx{ R"(([^]:\\[^]+\\game\\))" };
    std::smatch matches;

    if(not std::regex_search(dota_path, matches, rgx)) {
        qCritical() << "[MEMORY] Failed to find absolute dota 2 path.";
        return string();
    }

    return matches[1].str();
}

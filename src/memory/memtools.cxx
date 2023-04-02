#include "memtools.hxx"

#include <TlHelp32.h>
#include <QDebug>
#include <QtGlobal>

void Memory::linkToProcess(const char* name)
{
    Memory::base::processID = Memory::getProcessID(name);
    Memory::base::processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, Memory::base::processID);
    if(not Memory::base::processID)
        qCritical() << "[MEMORY] Process not found. Is process launched?";
    else
        qInfo().nospace() << "[MEMORY] Linked to process with ID: " << Memory::base::processID << ", HANDLE: " << Memory::base::processHandle;

    Memory::base::clientDll = Memory::getModuleBaseAddress(Memory::base::processID, "client.dll");
    Memory::base::serverDll = Memory::getModuleBaseAddress(Memory::base::processID, "server.dll");
    if(Memory::base::clientDll * Memory::base::serverDll)
        qDebug().nospace() << "[MEMORY] Entry points found. " << Qt::hex << "client.dll: 0x" << Memory::base::clientDll << ", server.dll: 0x" << Memory::base::serverDll << Qt::dec;
    else
        qCritical() << "[MEMORY] Entry point not found.";
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

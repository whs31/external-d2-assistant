#include "memory.h"



#include <TlHelp32.h>
#include <QDebug>
#include <QtGlobal>


unsigned long Memory::processID = 0;
void* Memory::handle = nullptr;
Offsets Memory::offsets = Offsets();

void Memory::linkToProcess(const char* name)
{
    processID = Memory::getProcessID(name);
    handle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);
    if(processID == 0)
        qCritical() << "[MEMORY] Process not found. Is process launched?";
    else
        qInfo().nospace() << "[MEMORY] Linked to process with ID: " << processID << ", HANDLE: " << handle;

    offsets.base.clientDll = Memory::getModuleBaseAddress(processID, "client.dll");
    offsets.base.serverDll = Memory::getModuleBaseAddress(processID, "server.dll");
    if(offsets.base.clientDll * offsets.base.serverDll != 0)
        qDebug().nospace() << "[MEMORY] Entry points found. " << Qt::hex << "client.dll: 0x" << offsets.base.clientDll << ", server.dll: 0x" << offsets.base.serverDll << Qt::dec;
    else
        qCritical() << "[MEMORY] Entry point not found.";
}

dword Memory::getProcessID(const char *procname)
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe;
    int pid = 0;
    BOOL hResult;

    // snapshot of all processes in the  system
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) return 0;

    // initializing size: needed for using Process32First
    pe.dwSize = sizeof(PROCESSENTRY32);

    // info about first process encountered in a system snapshot
    hResult = Process32First(hSnapshot, &pe);

    // retrieve information about the processes
    // and exit if unsuccessful
    while (hResult) {
        // if we find the process: return process ID
        #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        if (strstr(procname, pe.szExeFile)) {
        #elif QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        if (QString(modName) == QString::fromWCharArray(modEntry.szModule)) {
        #endif
            pid = pe.th32ProcessID;
            break;
        }
        hResult = Process32Next(hSnapshot, &pe);
    }

    // closes an open handle (CreateToolhelp32Snapshot)
    CloseHandle(hSnapshot);
    return pid;
}

uintptr Memory::getModuleBaseAddress(dword procId, const char*  modName)
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
                if (QString(procname) == QString::fromWCharArray(pe.szExeFile)) {
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

// wrapper для приватной имплементации сигскана
char* Memory::signatureScan(char* pattern, char* mask, char* begin, char* end, HANDLE* hProc)
{
    char* currentChunk = begin;
    char* match = nullptr;
    SIZE_T bytesRead;

    while (currentChunk < end)
    {
        MEMORY_BASIC_INFORMATION mbi;
        if (!VirtualQueryEx(hProc, currentChunk, &mbi, sizeof(mbi)))
            return nullptr;
        char* buffer = new char[mbi.RegionSize];
        if (mbi.State == MEM_COMMIT && mbi.Protect != PAGE_NOACCESS)
        {
            DWORD oldprotect;
            if (VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect))
            {
                ReadProcessMemory(hProc, mbi.BaseAddress, buffer, mbi.RegionSize, &bytesRead);
                VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, oldprotect, &oldprotect);
                char* internalAddress = Memory::signatureScanInternal(pattern, mask, buffer, bytesRead);
                if (internalAddress != nullptr)
                {
                    // internal -> external
                    uintptr_t offsetFromBuffer = internalAddress - buffer;
                    match = currentChunk + offsetFromBuffer;
                    delete[] buffer;
                    break;
                }
            }
        }
        currentChunk = currentChunk + mbi.RegionSize;
        delete[] buffer;
    }
    return match;
}

char* Memory::signatureScanInternal(char* pattern, char* mask, char* begin, unsigned int size)
{
    unsigned int patternLength = strlen(mask);
    for (unsigned int i = 0; i < size - patternLength; i++)
    {
        bool found = true;
        for (unsigned int j = 0; j < patternLength; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
            return (begin + i);
    }
    return nullptr;
}

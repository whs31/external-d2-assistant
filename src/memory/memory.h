#pragma once

#include <QtGlobal>
#include <cstdint>
#ifdef Q_OS_LINUX
#else
#include <windows.h>
#include "../sdk/classes/cexternalfunction.hpp"

namespace Memory {
    void linkToProcess(const char* process_name);

    template <typename T>
    T read(uintptr_t address);

    template <typename T>
    bool write(uintptr_t address, T value);

    uint32_t getProcessID(const char* procname);
    uintptr_t getModuleBaseAddress(uint32_t procId, const char* modName);

    template<typename T>
    inline T Memory::read(uintptr_t address)
    {
        T value;
        ReadProcessMemory(handle, (LPCVOID)address, &value, sizeof(T), NULL);
        return value;
    }

    template<typename T>
    inline bool Memory::write(uintptr_t address, T value)
    {
        return WriteProcessMemory(handle, (LPVOID)address, &value, sizeof(T), NULL);
    }

    CExternalFunction exportFunction(const char* moduleName, const char* exportName);
} /// namespace Memory;

#endif

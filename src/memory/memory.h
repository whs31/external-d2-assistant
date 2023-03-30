#pragma once

#include "offsets/offsets.h"
#include <cstdint>
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

    CExternalFunction exportFunction(const char* moduleName, const char* exportName);

    uint32_t countVM(void* _interface);

    bool isPointerValidForRead(uintptr_t ptr);
} /// namespace Memory;

template<typename T>
inline T Memory::read(uintptr_t address)
{
    T value;
    ReadProcessMemory(Memory::Base::processHandle, (LPCVOID)address, &value, sizeof(T), NULL);
    return value;
}

template<typename T>
inline bool Memory::write(uintptr_t address, T value)
{
    return WriteProcessMemory(Memory::Base::processHandle, (LPVOID)address, &value, sizeof(T), NULL);
}

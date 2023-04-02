#pragma once

#include <cstdint>
#include <windows.h>

namespace Memory {
    namespace base
    {
        inline uint32_t processID = 0;
        inline void* processHandle = nullptr;
        inline uintptr_t clientDll = 0;
        inline uintptr_t serverDll = 0;
    } /// namespace base;

    void linkToProcess(const char* process_name);

    template <typename T>
    T read(uintptr_t address);

    template <typename T>
    bool write(uintptr_t address, T value);

    uint32_t getProcessID(const char* procname);
    uintptr_t getModuleBaseAddress(uint32_t procId, const char* modName);
} /// namespace Memory;

template<typename T>
inline T Memory::read(uintptr_t address)
{
    T value;
    ReadProcessMemory(Memory::base::processHandle, (LPCVOID)address, &value, sizeof(T), NULL);
    return value;
}

template<typename T>
inline bool Memory::write(uintptr_t address, T value)
{
    return WriteProcessMemory(Memory::base::processHandle, (LPVOID)address, &value, sizeof(T), NULL);
}

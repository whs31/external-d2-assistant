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

    uint32_t getProcessID(const char* procname);
    uintptr_t getModuleBaseAddress(uint32_t procId, const char* modName);

    template<typename T>
    inline T read(uintptr_t address)
    {
        T value;
        ReadProcessMemory(base::processHandle, (LPCVOID)address, &value, sizeof(T), NULL);
        return value;
    }

    template<typename T>
    inline bool write(uintptr_t address, T value)
    {
        return WriteProcessMemory(base::processHandle, (LPVOID)address, &value, sizeof(T), NULL);
    }

} /// namespace Memory;

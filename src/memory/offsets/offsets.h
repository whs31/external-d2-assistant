#pragma once

#include <cstdint>

namespace Memory
{
    namespace Base
    {
        inline uint32_t processID = 0;
        inline void* processHandle = nullptr;
        inline uintptr_t clientDll = 0;
        inline uintptr_t serverDll = 0;
    } /// namespace Base;
} /// namespace Memory;


#pragma once

#include <cstdint>

namespace Memory
{
    namespace base
    {
        uint32_t processID = 0;
        void* processHandle = nullptr;

        uintptr_t clientDll = 0;
        uintptr_t serverDll = 0;
    } /// namespace base;
} /// namespace Memory;


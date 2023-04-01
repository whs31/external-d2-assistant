#pragma once
#include <cstdint>

#include "cexternalfunction.hpp"
#include "../macro.hpp"
#include "../../memory/memory.h"

// мб тут нужно враппер для экстернала писать. я не особо разбирался если честно)

class CVirtualClass
{
    vtable_entry;

    public:
        template <typename T>
        T getMember(ptrdiff_t offset);

        template <typename T>
        T getMemberPtr(ptrdiff_t offset);

        CExternalFunction getExternalFunction(size_t index)
        {
            uintptr_t vtable_ptr = Memory::read<uintptr_t>(((uintptr_t)this));
            uintptr_t entry_ptr = vtable_ptr + sizeof(uintptr_t) * index;

            return CExternalFunction(Memory::read<uintptr_t>((uintptr_t)entry_ptr));
        }

        template<uint32_t I, typename R = void*, typename ...T>
        R callExternalFunction(T...t) { return getExternalFunction(I).exec<R>(this, t...); }

};

template<typename T>
T CVirtualClass::getMember(ptrdiff_t offset)
{
    return *(T*)((uintptr_t)this + offset);
}

template<typename T>
T CVirtualClass::getMemberPtr(ptrdiff_t offset)
{
    return (T*)((uintptr_t)this + offset);
}


#pragma once
#include <cstdint>

#include "cexternalfunction.hpp"
#include "../macro.hpp"

// мб тут нужно враппер для экстернала писать. я не особо разбирался если честно)

class CVirtualClass
{
    vtable_entry;

    public:
        template <typename T>
        T getMember(ptrdiff_t offset);

        template <typename T>
        T getMemberPtr(ptrdiff_t offset);

        CExternalFunction getExternalFunction(size_t index);

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

inline CExternalFunction CVirtualClass::getExternalFunction(size_t index)
{
    uintptr_t vtable = *((uintptr_t*)(this));
    uintptr_t entry = vtable + sizeof(uintptr_t) * index;

    return CExternalFunction(*(uintptr_t*)entry);
}

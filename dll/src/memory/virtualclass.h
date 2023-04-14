#pragma once

#include <cstdint>
#include "function.h"
#include "memory.h"

namespace Memory
{
    inline Function getVirtualFunction(void* instance, int index) // aka getvfunc
    {
        uintptr_t vtable = *((uintptr_t*)(instance));
        uintptr_t entry = vtable + sizeof(uintptr_t) * index;
        return Function(*(uintptr_t*)entry);
    }

    struct VirtualClass {
        virtual void unused_vfunc() = 0;

        template<typename T>
        T& field(int offset) {
            if(not isValidForRead((uintptr_t)this + offset))
                throw "VirtualClass::field access violation";
            return *(T*)((uintptr_t)this + offset);
        }

        template<typename T>
        T member(int offset/*, T defaultValue = T{}*/) {
            if (!isValidForRead((uintptr_t)this + offset))
                return T{};
            return *(T*)((uintptr_t)this + offset);
        }

        // Gets a pointer to a type via the offset but does not dereference it
        template<typename T>
        T* memberInline(int offset) {
            return (T*)((uintptr_t)this + offset);
        }

        Function getVirtualFunction(int index) // aka GetVFunc
        {
            uintptr_t vtable = *((uintptr_t*)(this));
            uintptr_t entry = vtable + sizeof(uintptr_t) * index;
            return Function(*(uintptr_t*)entry);
        }

        template<uint32_t index, typename V = void*, typename ...T>
        V CallVFunc(T... t) {
            return getVirtualFunction(index).execute<V>(this, t...);
        }
    };
} // namespace Memory;

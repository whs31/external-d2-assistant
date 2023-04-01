#pragma once

#include <cstdint>

// мб тут нужно враппер для экстернала писать. я не особо разбирался если честно)

class CExternalFunction
{
    void* m_ptr;

    public:
        CExternalFunction(uintptr_t ptr);
        CExternalFunction(void* ptr);

        template <typename ...T>
        void* __fastcall operator()(T... t)
        {
            return (void*)((uintptr_t(__fastcall*)(T...))m_ptr)(t...);
        }

        void* __fastcall callWithCharPointerArg(const char* _ptr)
        {
            return (void*)((uintptr_t(__fastcall*)(const char*))m_ptr);
        }

        template <typename V, typename ...T>
        V __fastcall exec(T...t)
        {
            return ((V(__fastcall*)(T...))m_ptr)(t...);
        }

        void* get() const { return m_ptr; }
};

inline CExternalFunction::CExternalFunction(uintptr_t ptr)
    : m_ptr((void*)ptr)
{}

inline CExternalFunction::CExternalFunction(void* ptr)
    : m_ptr(ptr)
{}




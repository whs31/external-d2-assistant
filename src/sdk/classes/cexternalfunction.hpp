#pragma once

#include <QtGlobal>
#include <cstdint>

// мб тут нужно враппер для экстернала писать. я не особо разбирался если честно)

class CExternalFunction
{
    void* m_ptr;

    public:
        CExternalFunction(uintptr_t ptr);

        CExternalFunction(void* ptr);

        #ifdef Q_OS_LINUX

        template <typename ...T>
        void* operator()(T... t)
        {
            return (void*)((uintptr_t(T...))m_ptr)(t...);
        }

        template <typename V, typename ...T>
        V exec(T...t)
        {
            return ((V(T...))m_ptr)(t...);
        }

        #else

        template <typename ...T>
        void* __fastcall operator()(T... t)
        {
            return (void*)((uintptr_t(__fastcall*)(T...))m_ptr)(t...);
        }

        template <typename V, typename ...T>
        V __fastcall exec(T...t)
        {
            return ((V(__fastcall*)(T...))m_ptr)(t...);
        }

        #endif

        void* get() const { return m_ptr; }
};

inline CExternalFunction::CExternalFunction(uintptr_t ptr)
    : m_ptr((void*)ptr)
{}

inline CExternalFunction::CExternalFunction(void* ptr)
    : m_ptr(ptr)
{}


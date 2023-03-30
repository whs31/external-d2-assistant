#pragma once

#include <cstdint>
#include <cstddef>

namespace Memory {
    class Address
    {
        public:
            uintptr_t m_ptr;
        Address(uintptr_t ptr);
        Address(void* ptr);

        template <typename T>
        operator T() const { return (T)m_ptr; }

        Address offset(ptrdiff_t offset) { return Address(m_ptr + offset); }

        template <typename T = Address>
        T absoluteAddress(ptrdiff_t addressOffset, size_t opcodeSize) { return T(m_ptr + *(int*)(m_ptr + addressOffset) + opcodeSize); }

        template <typename T>
        T* as() const { return (T*)m_ptr; }
    };

    inline Address::Address(uintptr_t ptr)
        : m_ptr(ptr) {}

    inline Address::Address(void* ptr)
        : m_ptr((uintptr_t)ptr) {}

} /// namespace Memory;

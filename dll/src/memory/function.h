#pragma once

#include <cstdint>

namespace Memory
{
    //! @struct
    struct Function {

        //! @variable
        void* pointer;

        //! @brief
        Function(uintptr_t pointer) : pointer((void*)pointer) {}

        //! @brief
        Function(void* pointer) : pointer(pointer) {}

        //! @brief
        template<typename ...T>
        void* __fastcall operator()(T... t) {
            return (void*)((uintptr_t(__fastcall*)(T...))pointer)(t...);
        }

        //! @brief
        template<typename V, typename ...T>
        V __fastcall execute(T... t) {
            return ((V(__fastcall*)(T...))pointer)(t...);
        }
    };
} // namespace Memory;

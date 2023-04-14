#pragma once

#include <cstdint>
#include <vector>
#include "memory.h"

namespace Memory {
    inline uint32_t countVM(void* Interface) // aka CountVMs
    {
        auto** vmt = reinterpret_cast<uintptr_t**>(Interface);

        uint32_t methodCount = 0;

        while (vmt && (*vmt)[methodCount] && isValidForCode((*vmt)[methodCount]))
            methodCount++;

        return methodCount;
    }

    class VMT
    {
        public:
            uintptr_t* vmt;
            uintptr_t** vmInterface = nullptr;
            uintptr_t* vtable = nullptr;
            bool hasRTTI = false;
            int32_t rttiPrefix = 0;

            // rttiPrefix 2??? Wtf? Yeah read this: https://web.archive.org/web/20170701021444/https://spockwangs.github.io/2011/01/31/cpp-object-model.html
            explicit VMT(void* vmInterface, bool copyRTTI = true, int32_t rttiPrefixAmount = 2) {
                this->vmInterface = reinterpret_cast<uintptr_t**>(vmInterface);

                vtable = *this->vmInterface;

                int method_count = countVM(vmInterface) + 2 + rttiPrefixAmount;

                // Copy the Original Vtable.
                if (copyRTTI) {
                    vmt = new uintptr_t[method_count + 1];
                    memcpy(vmt, &vtable[-rttiPrefixAmount], (sizeof(uintptr_t) * method_count) + sizeof(uintptr_t));
                    hasRTTI = true;
                    rttiPrefix = rttiPrefixAmount;
                }
                else {
                    vmt = new uintptr_t[method_count];
                    memcpy(vmt, vtable, sizeof(uintptr_t) * method_count);
                }

                // Make sure to "NULL terminate" our new array of pointers.
                memset(&vmt[method_count], 0, sizeof(uintptr_t));
            }

            // Hook virtual method
            template <typename func = void*>
            func getVM(size_t methodIndex)
            {
                return (func)vmt[hasRTTI ? methodIndex + rttiPrefix : methodIndex];
            }
    };
} // namespace Memory;

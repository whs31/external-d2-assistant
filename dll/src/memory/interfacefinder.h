#pragma once

#include "memory.h"
#include "vmt.h"
#include <iostream>

namespace Memory
{
    template<typename T>
    inline T* findInterface(const char* dllName, const char* interfaceName, int vmCount = -1) {
        auto create_interface = exportFunction(dllName, "CreateInterface");
        int retCode = 0;
        void* result = create_interface(interfaceName, &retCode);

        int countedVMs = countVM(result);
        std::string vmInfo = " | VMs: " + std::to_string(countedVMs);
        if (vmCount != -1 && countedVMs != vmCount) {
            std::cout << "[INTERFACE MANAGER] VM mismatch" << std::endl;
        }
        std::cout << "[INTERFACE MANAGER] Found " << dllName << " | " << interfaceName << " | " << result << " | " << vmInfo << std::endl;
        return reinterpret_cast<T*>(result);
    }
} // namespace Memory;

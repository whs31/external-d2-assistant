#pragma once
#include "classes/cexternalfunction.hpp"
#include "classes/cvirtualclass.hpp"
#include "classes/entity/cgameentitysystem.hpp"
#include "../memory/memory.h"

#include <QDebug>

namespace Memory
{
    class ClassFinder
    {
        public:
            ClassFinder() = default;
            CVirtualClass* client;
            CGameEntitySystem* gameEntitySystem;

        template <typename T>
        inline T* getInterface(const char* moduleName, const char* interfaceName, int vmCount = -1)
        {
            CExternalFunction create = Memory::exportFunction(moduleName, "CreateInterface");
            int returnCode = 0;
            void* result = create.callWithCharPointerArg(interfaceName);

            //int count_vm = Memory::countVM(result);

            //if(vmCount != -1 and count_vm != vmCount)
            //    qWarning() << "[CLASSFINDER] Vm table mismatch detected.";
            return reinterpret_cast<T*>(result);
        }

        void find(); //сделать это не войдом, а структурой
    };
}

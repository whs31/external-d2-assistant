#pragma once

namespace Memory {
    class VirtualClass;
}

namespace Global
{
    class InterfaceManager
    {
        Memory::VirtualClass* source2client = nullptr;

        public:
            InterfaceManager();

            void findInterfaces();
    };
} // namespace Global;

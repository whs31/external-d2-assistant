#pragma once

class CGameEntitySystem;

namespace Memory {
    class VirtualClass;
}

namespace Global
{
    class InterfaceManager
    {
        Memory::VirtualClass* source2client = nullptr;
        CGameEntitySystem* gameEntitySystem = nullptr;

        public:
            InterfaceManager();

            void findInterfaces();
    };
} // namespace Global;

#include "interfacemanager.h"
#include "memory/interfacefinder.h"
#include "memory/virtualclass.h"
#include "dota/entity/cgameentitysystem.h"

#include <iostream>

using namespace Global;

InterfaceManager::InterfaceManager()
{

}

void InterfaceManager::findInterfaces()
{
    source2client = Memory::findInterface<Memory::VirtualClass>("client.dll", "Source2Client002");

    gameEntitySystem = *Memory::Address(source2client->getVirtualFunction(25).pointer).getAbsoluteAddress<CGameEntitySystem**>(3, 7);
    std::cout << "[INTERFACE MANAGER] Found CGameEntitySystem, " << gameEntitySystem->getHighestEntityIndex() << std::endl;

    // это просто тестовая итерация по энтити. ее можно убрать, нужна чисто для отладки
//    CEntityIdentity* start = gameEntitySystem->getIdentity(gameEntitySystem->getHighestEntityIndex());
//    std::cout << "Start: " << start->name() << std::endl;
//    while(start->m_pNext)
//    {
//        start = start->m_pNext;
//        std::cout << start->name() << std::endl;
//    }
}


#include "interfacemanager.h"
#include "memory/interfacefinder.h"
#include "memory/virtualclass.h"

using namespace Global;

InterfaceManager::InterfaceManager()
{

}

void InterfaceManager::findInterfaces()
{
    source2client = Memory::findInterface<Memory::VirtualClass>("client.dll", "Source2Client002");
}


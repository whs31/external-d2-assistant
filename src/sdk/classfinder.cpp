#include "classfinder.hpp"
#include "../memory/address.hpp"

void Memory::ClassFinder::find()
{
    client = getInterface<CVirtualClass>("client.dll", "Source2Client002");
    gameEntitySystem = *Memory::Address(client->getExternalFunction(25).get()).absoluteAddress<CGameEntitySystem**>(3, 7);
}

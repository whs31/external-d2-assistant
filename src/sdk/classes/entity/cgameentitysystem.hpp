#pragma once
#include "centityidentity.hpp"
#include "cabstractentitysystem.hpp"
#include "cbaseentity.hpp"

#define MAX_ENTITIES_IN_LIST 512
#define MAX_ENTITY_LISTS 64
#define MAX_TOTAL_ENTITIES MAX_ENTITIES_IN_LIST * MAX_ENTITY_LISTS

class CEntityIdentities
{
    public:
        CEntityIdentity identities[MAX_ENTITIES_IN_LIST];
};

class CGameEntitySystem : public CAbstractEntitySystem
{
    [[maybe_unused]] _unknown_value _0x8_1 [0x8];
    CEntityIdentities* m_EntityList[MAX_ENTITY_LISTS];

    public:
        CEntityIdentity* getIdentity(size_t index);

        template <typename T = CBaseEntity>
        T* getEntity(int index);

        size_t getHighestEntityIndex();
};

inline CEntityIdentity* CGameEntitySystem::getIdentity(size_t index)
{
    if(index <= -1 or index >= (MAX_TOTAL_ENTITIES - 1))
        return nullptr;

    CEntityIdentities* chunk = m_EntityList[(index / MAX_ENTITIES_IN_LIST)];

    if(not chunk)
        return nullptr;

    CEntityIdentity* identity = &chunk->identities[index % MAX_ENTITIES_IN_LIST];

    if(not identity)
        return nullptr;

    return identity;
}

inline size_t CGameEntitySystem::getHighestEntityIndex()
{
    return *(int*)((uintptr_t)this + 0x1510);
}

template<typename T>
T* CGameEntitySystem::getEntity(int index)
{
    CEntityIdentity* identity = getIdentity(index);
    if(identity)
        return (T*)identity->m_baseEntity;
    return nullptr;
}

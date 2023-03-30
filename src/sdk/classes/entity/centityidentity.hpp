#pragma once

#include "../../macro.hpp"
#include <cstdint>

class CBaseEntity;
class CEntityIdentity
{
    CBaseEntity* m_baseEntity;

    [[maybe_unused]] _unknown_value _0x8_1 [0x8];

    int32_t m_entityHandle;

    [[maybe_unused]] _unknown_value _0x4_1 [0x4];

    const char* m_internalName;
    const char* m_entityName;

    [[maybe_unused]] _unknown_value _0x8_2 [0x8];

    char m_flags[4];

    [[maybe_unused]] _unknown_value _0x24_1 [0x24];

    CEntityIdentity* m_previous;
    CEntityIdentity* m_next;
    CEntityIdentity* m_previousByClass;
    CEntityIdentity* m_nextByClass;

    public:
};

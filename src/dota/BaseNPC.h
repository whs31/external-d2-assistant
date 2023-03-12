#pragma once

#include <cstdint>
#include <cstddef>
#include <QDebug>

typedef int64_t UNUSED_64;
typedef int32_t UNUSED_32;

struct BaseNPC
{
    UNUSED_64 unknown_cbaseentity[99];

    int32_t maxHP;                          // 0x318
    int32_t currentHP;                      // 0x318 + 4
    uint8_t lifeState;                      // 0x318 + 5

    UNUSED_64 unknown_cbasenpc[226];
    UNUSED_32 unknown_0;

    int32_t currentLevel;                   // 0xA3C

    UNUSED_64 unknown_1[2];

    float hpRegen;                          // 0xA50

    UNUSED_64 unknown_2[5];
    UNUSED_32 unknown_3;

    int32_t moveSpeed;                      // 0xA84
    int32_t attackTime;                     // 0xA84 + 4

    UNUSED_64 unknown_4;
    UNUSED_32 unknown_5;

    float currentMana;                      // 0xA9C
    float maxMana;                          // 0xA9C + 4
    float manaRegen;                        // 0xA9C + 8

    UNUSED_64 unknown_6[42];
    UNUSED_32 unknown_7;

    int32_t heroID;

    friend QDebug operator<<(QDebug debug, const BaseNPC& n)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "BaseNPC Hero ID: " << n.heroID << ", max HP: " << n.maxHP << ", max MP: " << n.maxMana;

        return debug;
    }
};


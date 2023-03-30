#pragma once
#include "../../macro.hpp"
#include <cstdint>

class CBaseEntity;
class CAbstractEntitySystem
{
    public:
        unknown_virtual_func(_unknown_0);                                               // 0
        virtual void buildResourceManifest() = 0;                                       // 1
        unknown_virtual_func(_unknown_2);                                               // 2
        unknown_virtual_func(_unknown_3);                                               // 3
        unknown_virtual_func(_unknown_4);                                               // 4
        unknown_virtual_func(_unknown_5);                                               // 5
        unknown_virtual_func(_unknown_6);                                               // 6
        virtual void addRefKeyValues(void const*) = 0;                                  // 7
        virtual void releaseRefKeyValues(void const*) = 0;                              // 8
        unknown_virtual_func(_unknown_9);                                               // 9
        unknown_virtual_func(_unknown_10);                                              // 10
        virtual void clearEntityDatabase();                                             // 11
        virtual CBaseEntity* findEntityProcedural(const char* ...) = 0;                 // 12
        virtual CBaseEntity* onEntityParentChanged(CBaseEntity*, CBaseEntity*) = 0;     // 13
        virtual CBaseEntity* onAddEntity(CBaseEntity*, uint32_t) = 0;                   // 14
        virtual CBaseEntity* onRemoveEntity(CBaseEntity*, uint32_t) = 0;                // 15
        unknown_virtual_func(_unknown_16);                                              // 16
        virtual void sortEntities(int, void*, int*, int*) = 0;                          // 17
        unknown_virtual_func(_unknown_18);                                              // 18
        unknown_virtual_func(_unknown_19);                                              // 19
        unknown_virtual_func(_unknown_20);                                              // 20
        unknown_virtual_func(_unknown_21);                                              // 21
};

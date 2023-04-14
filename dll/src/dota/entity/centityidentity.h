#pragma once

#include "dota/shared/macro.h"

class CBaseEntity;
class CEntityIdentity {
    public:
        CBaseEntity* entity;
        void* dunno;
        int entHandle; // LOWORD(handle) & 0x7FFF = entID
        int unk2; // always seems to be -1
        const char* internalName; // these two strings are optional!
        const char* entityName; // ex: item_tpscroll

    private:
        void* unkptr3;

    public:
        char flags[4];

    private:
        char pad[4];
        void* unkptr4;
        void* unkptr5;
        void* unkptr6;
        void* unkptr8;

    public:
        CEntityIdentity* m_pPrev;
        CEntityIdentity* m_pNext;
        CEntityIdentity* m_pPrevByClass;
        CEntityIdentity* m_pNextByClass;

    public:
        const char* name() const {
            return internalName ? internalName : entityName;
        }

        bool isDormant() const {
            return (flags[0] & 0x80);
        }
};

#pragma once

#include "minhook/include/minhook.h"
#include <iostream>

inline bool hookFunctionImpl(void* func, void* detour, void* original, const char* name) {
    bool result = MH_CreateHook(func, detour,
                                (LPVOID*)original) == MH_OK &&
                  MH_EnableHook(func) == MH_OK;
    if(not result)
        std::cout << "[MINHOOK] Could not hook" << name << "()!\n";
    return result;
};
#define hookFunction(func) HookFunc(func, &hk##func, &o##func, #func)

#pragma once
#include <cstdint>
#define __global_const constexpr static inline

namespace Config
{
    __global_const bool LAUNCH_GAME_ON_STARTUP = true;
    __global_const bool INJECT_ON_STARTUP = true;
    __global_const uint32_t INJECT_DELAY = 15000;
} // namespace Config;

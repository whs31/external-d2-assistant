#pragma once

#include <cstdint>
#define __struct_packed struct __attribute((packed))

namespace UDP
{
    __struct_packed DatagramHeader
    {
        uint8_t messageType = 0;
        uint16_t messageId = 0;
        uint32_t messageSize = 0;
    };

    __struct_packed DatagramData{
        uint32_t dataSize = 0;
        char* data = nullptr;
    };
} // namespace UDP;

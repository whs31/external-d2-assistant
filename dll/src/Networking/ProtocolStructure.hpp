#ifndef PROTOCOLSTRUCTURE_HPP
#define PROTOCOLSTRUCTURE_HPP
#include <cstdint>

struct __attribute__((packed)) DatagramHeader{
    uint8_t messageType = 0;
    uint16_t messageId = 0;
    uint32_t messageSize = 0;
};

struct __attribute__((packed)) DatagramData{
    uint32_t dataSize = 0;
    char * data = nullptr;
};

#endif // PROTOCOLSTRUCTURE_HPP

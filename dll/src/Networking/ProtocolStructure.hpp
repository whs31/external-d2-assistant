#ifndef PROTOCOLSTRUCTURE_H
#define PROTOCOLSTRUCTURE_H
#include <cstdint>

template<typename T>
struct __attribute__((packed)) DatagramStructure{
    uint8_t messageType = 0;
    uint16_t messageId = 0;
    uint32_t messageSize = 0;
    T data;
};

#endif // PROTOCOLSTRUCTURE_H

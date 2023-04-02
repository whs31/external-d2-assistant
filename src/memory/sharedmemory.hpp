#ifndef SHAREDMEMORY_HP
#define SHAREDMEMORY_HP

#include <cstdint>
#include <memory>
#include <windows.h>

namespace SharedMemory {
bool createSharedMemory(const LPCWSTR& _sharedMemoryName, const uint16_t _bufferSize = 8);

HANDLE openSharedMemory(const LPCWSTR& _sharedMemoryName);

bool whriteToSharedMemory(const HANDLE& _handle, const char _dataToWrite[], const uint16_t _bufferSize = 8);

std::unique_ptr<char[]> readFromSharedMemory(const HANDLE& _handle, uint16_t _bytesCount, const uint16_t _bufferSize = 8);
}

#endif // SHAREDMEMORY_HP

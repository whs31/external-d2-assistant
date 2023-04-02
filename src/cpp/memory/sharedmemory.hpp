#pragma once

#include <cstdint>
#include <memory>
#include <windows.h>
#include <QtGlobal>

namespace Memory {
    namespace shared {
        #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        bool createSharedMemory(const LPCWSTR& _sharedMemoryName, const uint16_t _bufferSize = 8);

        HANDLE openSharedMemory(const LPCWSTR& _sharedMemoryName);
        #else
        bool createSharedMemory(const LPCSTR& _sharedMemoryName, const uint16_t _bufferSize = 8);

        HANDLE openSharedMemory(const LPCSTR& _sharedMemoryName);
        #endif

        bool writeToSharedMemory(const HANDLE& _handle, const char _dataToWrite[], const uint16_t _bufferSize = 8);

        std::unique_ptr<char[]> readFromSharedMemory(const HANDLE& _handle, uint16_t _bytesCount, const uint16_t _bufferSize = 8);
    }
}

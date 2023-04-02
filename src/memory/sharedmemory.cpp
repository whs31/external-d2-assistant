#include "sharedmemory.hpp"
#include <tchar.h>
#include <iostream>

bool SharedMemory::createSharedMemory(const LPCWSTR& _sharedMemoryName, const uint16_t _bufferSize) {
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, _bufferSize, _sharedMemoryName);
    if (!hMapFile) {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"), GetLastError());
        return false;
    }
    return true;
}

HANDLE SharedMemory::openSharedMemory(const LPCWSTR& _sharedMemoryName) {
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, _sharedMemoryName);
    if (!hMapFile) {
        _tprintf(TEXT("Could not open file mapping object (%d).\n"), GetLastError());
        return nullptr;
    }
    return hMapFile;
}

bool SharedMemory::whriteToSharedMemory(const HANDLE& _handle, const char _dataToWrite[], const uint16_t _bufferSize) {
    //неправльный расчет размера данных для записи в memcpy

    LPCTSTR pBuf = (LPTSTR)MapViewOfFile(_handle, FILE_MAP_ALL_ACCESS, 0, 0, _bufferSize);

    if (!pBuf)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());
        CloseHandle(_handle);
        return false;
    }
    //std::cout << _tcslen(_dataToWrite)<<std::endl;
    std::cout << sizeof(_dataToWrite) << std::endl;
    memcpy((void*)pBuf, _dataToWrite, 9 * sizeof(wchar_t));
    UnmapViewOfFile(pBuf);
    return true;
}

std::unique_ptr<char[]> SharedMemory::readFromSharedMemory(const HANDLE& _handle, uint16_t _bytesCount, const uint16_t _bufferSize) {
    LPCTSTR pBuf = (LPTSTR)MapViewOfFile(_handle, FILE_MAP_ALL_ACCESS, 0, 0, _bufferSize);
    auto result = std::unique_ptr<char[]>(new char[_bytesCount]);
    if (pBuf == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());

        CloseHandle(_handle);
        return std::move(result);
    }
    memcpy(result.get(), pBuf, _bytesCount);

    return std::move(result);
}

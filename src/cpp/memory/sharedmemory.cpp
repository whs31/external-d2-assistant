#include "sharedmemory.hpp"

#include <tchar.h>
#include <iostream>
#include <QtGlobal>

#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
bool Memory::shared::createSharedMemory(const LPCWSTR& _sharedMemoryName, const uint16_t _bufferSize) {
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, _bufferSize, _sharedMemoryName);
    if (!hMapFile) {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"), GetLastError());
        return false;
    }
    return true;
}


HANDLE Memory::shared::openSharedMemory(const LPCWSTR& _sharedMemoryName) {
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, _sharedMemoryName);
    if (!hMapFile) {
        _tprintf(TEXT("Could not open file mapping object (%d).\n"), GetLastError());
        return nullptr;
    }
    return hMapFile;
}
#else
bool Memory::shared::createSharedMemory(const LPCSTR& _sharedMemoryName, const uint16_t _bufferSize) {
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, _bufferSize, _sharedMemoryName);
    if (!hMapFile) {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"), GetLastError());
        return false;
    }
    return true;
}


HANDLE Memory::shared::openSharedMemory(const LPCSTR& _sharedMemoryName) {
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, _sharedMemoryName);
    if (!hMapFile) {
        _tprintf(TEXT("Could not open file mapping object (%d).\n"), GetLastError());
        return nullptr;
    }
    return hMapFile;
}
#endif

bool Memory::shared::writeToSharedMemory(const HANDLE& _handle, const char _dataToWrite[], const uint16_t _bufferSize) {
    //неправльный расчет размера данных для записи в memcpy

    LPCTSTR pBuf = (LPTSTR)MapViewOfFile(_handle, FILE_MAP_ALL_ACCESS, 0, 0, _bufferSize);

    if (!pBuf)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());
        CloseHandle(_handle);
        return false;
    }
    //std::cout << sizeof(_dataToWrite) << std::endl;
    memcpy((void*)pBuf, _dataToWrite, 9 * sizeof(wchar_t));
    UnmapViewOfFile(pBuf);
    return true;
}


std::unique_ptr<char[]> Memory::shared::readFromSharedMemory(const HANDLE& _handle, uint16_t _bytesCount, const uint16_t _bufferSize) {
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

#pragma once
#include <windows.h>

typedef unsigned long long uintptr;
typedef unsigned long dword;

class Memory
{

public:
    Memory() = default;

    static void linkToProcess(const char* process_name);

    template <typename T>
    static T read(uintptr address);

    template <typename T>
    static bool write(uintptr address, T value);

    static char* signatureScan(char* pattern, char* mask, char* begin, char* end, HANDLE* hproc);

    static dword getProcessID(const char *procname);
    static uintptr getModuleBaseAddress(dword procId, const char*  modName);

public:
    static unsigned long processID;
    static void* handle;

private:
    static char* signatureScanInternal(char* pattern, char* mask, char* begin, unsigned int size);
};

template<typename T>
inline T Memory::read(uintptr address)
{
    T value;
    ReadProcessMemory(handle, (LPCVOID)address, &value, sizeof(T), NULL);
    return value;
}

template<typename T>
inline bool Memory::write(uintptr address, T value)
{
    return WriteProcessMemory(handle, (LPVOID)address, &value, sizeof(T), NULL);
}




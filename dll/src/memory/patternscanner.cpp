#include "patternscanner.h"
#include "winprocess.h"

void* Memory::patternScan(char *base, size_t size, const char *pattern, const char *mask)
{
    size_t patternLength = strlen(mask);

    for(unsigned int i = 0; i < size - patternLength; ++i)
    {
        bool found = true;
        for(unsigned int j = 0; j < patternLength; ++j)
        {
            if(mask[j] != '?' and pattern[j] != *(base + i + j))
            {
                found = false;
                break;
            }
        }

        if(found)
            return (void*)(base + i);
    }
    return nullptr;
}

void* Memory::patternScanEx(HANDLE hPRocess, uintptr_t begin, uintptr_t end, const char *pattern, const char *mask)
{
    uintptr_t currentChunk = begin;
    size_t patternSize = strlen(pattern);
    while(currentChunk < end)
    {
        void* internalAddress = Memory::patternScan((char*)currentChunk, patternSize + 1, pattern, mask);

        if(internalAddress)
        {
            uintptr_t offsetFromBuffer = (uintptr_t)internalAddress - currentChunk;
            return (void*)(currentChunk + offsetFromBuffer);
        }
        else
            currentChunk++;
    }
    return nullptr;
}

void *patternScanExModule(HANDLE hProcess, DWORD processID, const wchar_t *module, const char *pattern, const char *mask)
{
    MODULEENTRY32 modEntry = Memory::getModuleEntry(processID, module);

    if(not modEntry.th32ModuleID)
        return nullptr;

    uintptr_t begin = (uintptr_t)modEntry.modBaseAddr;
    uintptr_t end = begin + modEntry.modBaseSize;
    return Memory::patternScanEx(hProcess, begin, end, pattern, mask);
}

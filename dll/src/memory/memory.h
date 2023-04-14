#pragma once
#include <cstdint>
#include <string>
#include "patternscanner.h"
#include "function.h"

namespace Memory
{
    class Address {
        public:
            uintptr_t pointer;

            Address(uintptr_t pointer) : pointer(pointer) {}
            Address(void* pointer) : pointer((uintptr_t)pointer) {}

            template<typename T>
            operator T() const
            {
                return (T)pointer;
            }

            Address offset(int offset) {
                return Address(pointer + offset);
            }

            template<typename T = Address>
            T getAbsoluteAddress(int address_offset, int sizeof_opcode = -1) const {
                if (sizeof_opcode == -1)
                    sizeof_opcode = address_offset + sizeof(uint32_t);
                return T(pointer + *(int*)(pointer + address_offset) + sizeof_opcode);
            }

            template<typename T>
            T* as() const {
                return (T*)pointer;
            }
    };

    class ScanContext {
        //Splits IDA pattern into code mask/pattern
        void parse(const char* combo, std::string& pattern, std::string& mask)
        {
            unsigned int patternLen = (strlen(combo) + 1) / 3;
            int index = 0;
            for (unsigned int i = 0; i < strlen(combo); i++)
            {
                if (combo[i] == ' ')
                    continue;
                else if (combo[i] == '?')
                {
                    mask += '?';
                    pattern += '\x00';
                    i++;
                }
                else
                {
                    char byte = (char)strtol(&combo[i], 0, 16);
                    pattern += byte;
                    mask += 'x';
                    i += 2;
                }
            }
            //pattern += '\0';
            //mask = '\0';
        }

        public:

        HANDLE procHandle;
        int pid;

        ScanContext(HANDLE procHandle, int pid) : procHandle(procHandle), pid(pid) {}

        Address scan(const std::string& signature, const wchar_t* moduleName) {
            int maskLength = (signature.length() + 1) / 3 + 1;
            std::string pattern, mask;
            pattern.reserve(maskLength);
            mask.reserve(maskLength);

            parse(signature.c_str(), pattern, mask);

            Address result(patternScanExModule(procHandle, pid, moduleName, pattern.c_str(), mask.c_str()));
            return result;
        }
    };

    template <typename T>
    inline void memcopy(T dst, T src, size_t size) {
        memcpy((void*)dst, (const void*)src, size);
    }

    // Returns an exported function, if it's available
    inline Function exportFunction(const char* dllName, const char* exportName) { // aka GetExport
        return Function((void*)GetProcAddress(GetModuleHandleA(dllName), exportName));
    }

    template<typename T = uintptr_t>
    inline bool isValidForRead(T p) { // aka IsValidReadPtr
        if (!p)
            return false;
        MEMORY_BASIC_INFORMATION mbi;
        memset(&mbi, 0, sizeof(mbi));
        if (!VirtualQuery((void*)p, &mbi, sizeof(mbi)))
            return false;
        if (!(mbi.State & MEM_COMMIT))
            return false;
        if (!(mbi.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY |
                             PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
            return false;
        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
            return false;
        return true;
    }

    template<typename T = uintptr_t>
    inline bool isValidForWrite(T p) // aka IsValidWritePtr
    {
        MEMORY_BASIC_INFORMATION mbi;
        memset(&mbi, 0, sizeof(mbi));
        if (!VirtualQuery((void*)p, &mbi, sizeof(mbi)))
            return false;
        if (!(mbi.State & MEM_COMMIT))
            return false;
        if (!(mbi.Protect & (PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
            return false;
        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
            return false;
        return true;
    }

    template<typename T = uintptr_t>
    inline bool isValidForCode(T p) // aka IsValidCodePtr
    {
        MEMORY_BASIC_INFORMATION mbi;
        memset(&mbi, 0, sizeof(mbi));
        if (!VirtualQuery((void*)p, &mbi, sizeof(mbi)))
            return false;
        if (!(mbi.State & MEM_COMMIT))
            return false;
        if (!(mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
            return false;
        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
            return false;
        return true;
    }
} // namespace Memory;

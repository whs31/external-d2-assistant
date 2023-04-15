#pragma once

#include <cstdint>
#include <windows.h>
#include <QString>

//! @namespace Namespace for working with memory.
namespace Memory {
    //! @namespace Subnamespace for classes, variables and functions,
    //!            storing and processing the key values of memory operations.
    namespace base
    {
        inline uint32_t processID = 0;          //! @variable Dota 2 process ID
        inline void* processHandle = nullptr;   //! @variable Dota 2 process handle
        inline uintptr_t clientDll = 0;         //! @variable Client.dll global module address
        inline uintptr_t serverDll = 0;         //! @variable Server.dll global module address

        inline QString dotaGameFolder;          //! @variable Dota 2 game folder absolute path
        inline QString dotaBinaryFolder;        //! @variable Dota 2 binaries folder absolute path
        inline QString dotaExecutable;          //! @variable Dota2.exe absolute path

        inline QString internalLib;             //! @variable Internal .dll lib absolute path
    } /// namespace base;

    //! @brief Finds process by name, gets handle, client.dll +
    //!        server.dll addresses and process ID.
    //! @param process_name - process name to find.
    //! @return Function execution result.
    bool linkToProcess(const char* process_name);

    //! @brief Gets process ID by name.
    //! @param procname - process name (e. g, dota2.exe).
    //! @return Process ID.
    uint32_t getProcessID(const char* procname);

    //! @brief Gets module global address by name and parent process ID.
    //! @param procID - parent process ID.
    //! @param modName - module name.
    //! @return Module address in global memory.
    uintptr_t getModuleBaseAddress(uint32_t procId, const char* modName);

    //! @brief Reads value of type T from address in global memory.
    //! @param T - value type to read.
    //! @param address - value global memory address.
    //! @return Value.
    template<typename T>
    inline T read(uintptr_t address)
    {
        T value;
        ReadProcessMemory(base::processHandle, (LPCVOID)address, &value, sizeof(T), NULL);
        return value;
    }

    //! @brief Writes value of type T from address in global memory.
    //! @param T - value type to write.
    //! @param value - value of T to write.
    //! @param address - value global memory address.
    //! @return Function execution result.
    template<typename T>
    inline bool write(uintptr_t address, T value)
    {
        return WriteProcessMemory(base::processHandle, (LPVOID)address, &value, sizeof(T), NULL);
    }

    //! @todo
    BOOL remoteFunction(HANDLE hProcess, LPCSTR lpModuleName, LPCSTR lpProcName, LPVOID lpParameters, SIZE_T dwParamSize, PVOID *ppReturn);

    //! @namespace registry - subnamespace for functions, working with
    //!            Windows registry.
    namespace registry
    {
        //! @brief Returns dota 2 folder address from registry.
        //! @return Absolute path in file system.
        std::string getGamePathFromRegistry();

        //! @brief Returns dota 2 folder absolute path.
        //! @return Absolute path in file system.
        std::string getGamePath();
    } // namespace registry;
} // namespace Memory;

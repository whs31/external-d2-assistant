#pragma once

#include <cstdint>
#include <windows.h>
#include <QString>

//! @namespace Memory - пространство имен для функций и полей,
//!            работающих с глобальной памятью и регистром Windows.
namespace Memory {
    //! @namespace base - подпространство имен для полей, используемых
    //!            при работе с памятью.
    namespace base
    {
        inline uint32_t processID = 0;          //! @variable ID процесса доты
        inline void* processHandle = nullptr;   //! @variable HANDLE процесса доты
        inline uintptr_t clientDll = 0;         //! @variable Адрес client.dll
        inline uintptr_t serverDll = 0;         //! @variable Адрес server.dll

        inline QString dotaGameFolder;          //! @variable Абсолютный путь к папке с дотой
        inline QString dotaBinaryFolder;        //! @variable Абсолютный путь к папке с dota2.exe
        inline QString dotaExecutable;          //! @variable Абсолютный путь к dota2.exe

        inline QString internalLib;             //! @variable Абсолютный путь к динамической либе для инжекта
    } /// namespace base;

    //! @brief Находит процесс по имени, получает его HANDLE, адреса client.dll и
    //!        server.dll, и PID.
    //! @param process_name - имя процесса для поиска.
    //! @return Результат выполнения функции.
    bool linkToProcess(const char* process_name);

    //! @brief Получает PID процесса по его имени.
    //! @param procname - имя процесса (например, dota2.exe).
    //! @return PID процесса.
    uint32_t getProcessID(const char* procname);

    //! @brief Получает адрес модуля по его имени и айди процесса.
    //! @param procID - ID процесса для поиска.
    //! @param modName - имя модуля для поиска.
    //! @return Указатель на модуль в глобальной памяти.
    uintptr_t getModuleBaseAddress(uint32_t procId, const char* modName);

    //! @brief Читает память размером sizeof(T) по заданному адресу.
    //! @param T - тип данных для чтения.
    //! @param address - адрес в глобальной памяти.
    //! @return Значение по указанному адресу.
    template<typename T>
    inline T read(uintptr_t address)
    {
        T value;
        ReadProcessMemory(base::processHandle, (LPCVOID)address, &value, sizeof(T), NULL);
        return value;
    }

    //! @brief Пишет значение размером sizeof(T) в заданный адрес.
    //! @param T - тип данных для записи.
    //! @param value - значение T для записи.
    //! @param address - адрес в глобальной памяти.
    //! @return Результат выполнения функции.
    template<typename T>
    inline bool write(uintptr_t address, T value)
    {
        return WriteProcessMemory(base::processHandle, (LPVOID)address, &value, sizeof(T), NULL);
    }

    //! @namespace registry - подпространство имен для функций и полей,
    //!            используемых при работе с регистром Windows.
    namespace registry
    {
        //! @brief Возвращает путь к папке с dota 2 из регистра.
        //! @return Абсолютный путь в файловой системе.
        std::string getGamePathFromRegistry();

        //! @brief Возвращает абсолютный путь к папке с dota 2.
        //! @return Абсолютный путь к папке.
        std::string getGamePath();
    } /// namespace registry;
} /// namespace Memory;

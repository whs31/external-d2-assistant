#include "winapiwrapper.hpp"

#include <commctrl.h>
#include <psapi.h>
#include <string>
#include <sdkddkver.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


HMODULE WinAPIExtended::getExternalModuleHandle(HANDLE hProcess, LPCSTR lpModuleName)
{
    HMODULE* ModuleArray = NULL;
    DWORD ModuleArraySize = 100;
    DWORD NumModules = 0;
    CHAR lpModuleNameCopy[MAX_PATH] = {0};
    CHAR ModuleNameBuffer[MAX_PATH] = {0};

    if(lpModuleName == NULL)
        goto GRMH_FAIL_JMP;

    for (size_t i = 0; lpModuleName[i] != '\0'; ++i)
    {
        if (lpModuleName[i] >= 'A' && lpModuleName[i] <= 'Z')
            lpModuleNameCopy[i] = lpModuleName[i] + 0x20;
        else
            lpModuleNameCopy[i] = lpModuleName[i];

        lpModuleNameCopy[i+1] = '\0';
    }

    ModuleArray = new HMODULE[ModuleArraySize];

    if(ModuleArray == NULL)
        goto GRMH_FAIL_JMP;

    if(!::EnumProcessModulesEx(hProcess, ModuleArray,
                                ModuleArraySize * sizeof(HMODULE), &NumModules, LIST_MODULES_ALL))
        goto GRMH_FAIL_JMP;

    NumModules /= sizeof(HMODULE);

    if(NumModules > ModuleArraySize)
    {
        delete[] ModuleArray;
        ModuleArray = NULL;
        ModuleArray = new HMODULE[NumModules];

        if(ModuleArray == NULL)
            goto GRMH_FAIL_JMP;

        ModuleArraySize = NumModules;

        if( !::EnumProcessModulesEx(hProcess, ModuleArray,
                                    ModuleArraySize * sizeof(HMODULE), &NumModules, LIST_MODULES_ALL) )
            goto GRMH_FAIL_JMP;

        NumModules /= sizeof(HMODULE);
    }

    for(DWORD i = 0; i <= NumModules; ++i)
    {
        ::GetModuleBaseName(hProcess, ModuleArray[i],
                            ModuleNameBuffer, sizeof(ModuleNameBuffer));

        if(strstr(ModuleNameBuffer, lpModuleNameCopy) != NULL)
        {
            HMODULE TempReturn = ModuleArray[i];
            delete[] ModuleArray;
            return TempReturn;
        }
    }

GRMH_FAIL_JMP:
    if(ModuleArray != NULL)
        delete[] ModuleArray;
    return NULL;
}

FARPROC WinAPIExtended::getExternalProcAddress(HANDLE hProcess, HMODULE hModule, LPCSTR lpProcName, UINT Ordinal, WINBOOL useOrdinal)
{
    BOOL Is64Bit = FALSE;
    MODULEINFO RemoteModuleInfo = {0};
    UINT_PTR RemoteModuleBaseVA = 0;
    IMAGE_DOS_HEADER DosHeader = {0};
    DWORD Signature = 0;
    IMAGE_FILE_HEADER FileHeader = {0};
    IMAGE_OPTIONAL_HEADER64 OptHeader64 = {0};
    IMAGE_OPTIONAL_HEADER32 OptHeader32 = {0};
    IMAGE_DATA_DIRECTORY ExportDirectory = {0};
    IMAGE_EXPORT_DIRECTORY ExportTable = {0};
    UINT_PTR ExportFunctionTableVA = 0;
    UINT_PTR ExportNameTableVA = 0;
    UINT_PTR ExportOrdinalTableVA = 0;
    DWORD* ExportFunctionTable = NULL;
    DWORD* ExportNameTable = NULL;
    WORD* ExportOrdinalTable = NULL;

    CHAR TempChar;
    BOOL Done = FALSE;

    if(lpProcName == NULL and not useOrdinal)
        goto GRPA_FAIL_JMP;

    if(!::GetModuleInformation(hProcess, hModule,&RemoteModuleInfo, sizeof(RemoteModuleInfo)))
        goto GRPA_FAIL_JMP;
    RemoteModuleBaseVA = (UINT_PTR)RemoteModuleInfo.lpBaseOfDll;

    if(!::ReadProcessMemory(hProcess, (LPCVOID)RemoteModuleBaseVA, &DosHeader,
                             sizeof(DosHeader), NULL) || DosHeader.e_magic != IMAGE_DOS_SIGNATURE)
        goto GRPA_FAIL_JMP;

    if(!::ReadProcessMemory(hProcess, (LPCVOID)(RemoteModuleBaseVA + DosHeader.e_lfanew),
                             &Signature, sizeof(Signature), NULL) || Signature != IMAGE_NT_SIGNATURE)
        goto GRPA_FAIL_JMP;

    if(!::ReadProcessMemory(hProcess,
                             (LPCVOID)(RemoteModuleBaseVA + DosHeader.e_lfanew + sizeof(Signature)),
                             &FileHeader, sizeof(FileHeader), NULL))
        goto GRPA_FAIL_JMP;

    if(FileHeader.SizeOfOptionalHeader == sizeof(OptHeader64))
        Is64Bit = TRUE;
    else if(FileHeader.SizeOfOptionalHeader == sizeof(OptHeader32))
        Is64Bit = FALSE;
    else
        goto GRPA_FAIL_JMP;

    if(Is64Bit)
    {
        if(!::ReadProcessMemory(hProcess,
                                 (LPCVOID)(RemoteModuleBaseVA + DosHeader.e_lfanew + sizeof(Signature) + sizeof(FileHeader)),
                                 &OptHeader64, FileHeader.SizeOfOptionalHeader, NULL)
            || OptHeader64.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
            goto GRPA_FAIL_JMP;
    }
    else
    {
        if(!::ReadProcessMemory(hProcess,
                                 (LPCVOID)(RemoteModuleBaseVA + DosHeader.e_lfanew + sizeof(Signature) + sizeof(FileHeader)),
                                 &OptHeader32, FileHeader.SizeOfOptionalHeader, NULL)
            || OptHeader32.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
            goto GRPA_FAIL_JMP;
    }

    if(Is64Bit && OptHeader64.NumberOfRvaAndSizes >= IMAGE_DIRECTORY_ENTRY_EXPORT + 1)
    {
        ExportDirectory.VirtualAddress = (OptHeader64.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).VirtualAddress;
        ExportDirectory.Size = (OptHeader64.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).Size;
    }
    else if(OptHeader32.NumberOfRvaAndSizes >= IMAGE_DIRECTORY_ENTRY_EXPORT + 1)
    {
        ExportDirectory.VirtualAddress = (OptHeader32.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).VirtualAddress;
        ExportDirectory.Size = (OptHeader32.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).Size;
    }
    else
        goto GRPA_FAIL_JMP;

    if(!::ReadProcessMemory(hProcess, (LPCVOID)(RemoteModuleBaseVA + ExportDirectory.VirtualAddress),
                             &ExportTable, sizeof(ExportTable), NULL))
        goto GRPA_FAIL_JMP;

    ExportFunctionTableVA = RemoteModuleBaseVA + ExportTable.AddressOfFunctions;
    ExportNameTableVA = RemoteModuleBaseVA + ExportTable.AddressOfNames;
    ExportOrdinalTableVA = RemoteModuleBaseVA + ExportTable.AddressOfNameOrdinals;

    ExportFunctionTable	= new DWORD[ExportTable.NumberOfFunctions];
    ExportNameTable		= new DWORD[ExportTable.NumberOfNames];
    ExportOrdinalTable	= new WORD[ExportTable.NumberOfNames];

    if(ExportFunctionTable == NULL || ExportNameTable == NULL || ExportOrdinalTable == NULL)
        goto GRPA_FAIL_JMP;

    if(!::ReadProcessMemory(hProcess, (LPCVOID)ExportFunctionTableVA,
                             ExportFunctionTable, ExportTable.NumberOfFunctions * sizeof(DWORD), NULL))
        goto GRPA_FAIL_JMP;

    if(!::ReadProcessMemory(hProcess, (LPCVOID)ExportNameTableVA,
                             ExportNameTable, ExportTable.NumberOfNames * sizeof(DWORD), NULL))
        goto GRPA_FAIL_JMP;

    if(!::ReadProcessMemory(hProcess, (LPCVOID)ExportOrdinalTableVA,
                             ExportOrdinalTable, ExportTable.NumberOfNames * sizeof(WORD), NULL))
        goto GRPA_FAIL_JMP;

    if(useOrdinal)
    {
        if(Ordinal < ExportTable.Base || (Ordinal - ExportTable.Base) >= ExportTable.NumberOfFunctions)
            goto GRPA_FAIL_JMP;

        UINT FunctionTableIndex = Ordinal - ExportTable.Base;

        if(ExportFunctionTable[FunctionTableIndex] >= ExportDirectory.VirtualAddress &&
            ExportFunctionTable[FunctionTableIndex] <= ExportDirectory.VirtualAddress + ExportDirectory.Size)
        {
            Done = FALSE;
            std::string TempForwardString;
            TempForwardString.clear();

            for(UINT_PTR i = 0; !Done; ++i)
            {
                /* Get next character */
                if(!::ReadProcessMemory(hProcess,
                                         (LPCVOID)(RemoteModuleBaseVA + ExportFunctionTable[FunctionTableIndex] + i),
                                         &TempChar, sizeof(TempChar), NULL))
                    goto GRPA_FAIL_JMP;

                TempForwardString.push_back(TempChar); // Add it to the string

                /* If it's NUL we are done */
                if(TempChar == (CHAR)'\0')
                    Done = TRUE;
            }

            size_t Dot = TempForwardString.find('.');
            if(Dot == std::string::npos)
                goto GRPA_FAIL_JMP;

            std::string RealModuleName, RealFunctionId;
            RealModuleName = TempForwardString.substr(0, Dot - 1);
            RealFunctionId = TempForwardString.substr(Dot + 1, std::string::npos);

            HMODULE RealModule = WinAPIExtended::getExternalModuleHandle(hProcess, RealModuleName.c_str());
            FARPROC TempReturn;

            if(RealFunctionId.at(0) == '#')
            {
                UINT RealOrdinal = 0;
                RealFunctionId.erase(0, 1);

                for(size_t i = 0; i < RealFunctionId.size(); ++i)
                {
                    if(RealFunctionId[i] >= '0' && RealFunctionId[i] <= '9')
                    {
                        RealOrdinal *= 10;
                        RealOrdinal += RealFunctionId[i] - '0';
                    }
                    else
                        break;
                }

                TempReturn = WinAPIExtended::getExternalProcAddress(hProcess, RealModule, NULL, RealOrdinal, TRUE);
            }
            else
                TempReturn = WinAPIExtended::getExternalProcAddress(hProcess, RealModule, RealFunctionId.c_str(), 0, FALSE);

            delete[] ExportFunctionTable;
            delete[] ExportNameTable;
            delete[] ExportOrdinalTable;
            return TempReturn;
        }
        else
        {
            FARPROC TempReturn = (FARPROC)(RemoteModuleBaseVA + ExportFunctionTable[FunctionTableIndex]);

            delete[] ExportFunctionTable;
            delete[] ExportNameTable;
            delete[] ExportOrdinalTable;

            return TempReturn;
        }
    }

    for(DWORD i = 0; i < ExportTable.NumberOfNames; ++i)	{
        std::string TempFunctionName;

        Done = FALSE;
        TempFunctionName.clear();

        for(UINT_PTR j = 0; !Done; ++j)
        {
            if(!::ReadProcessMemory(hProcess, (LPCVOID)(RemoteModuleBaseVA + ExportNameTable[i] + j),
                                     &TempChar, sizeof(TempChar), NULL))
                goto GRPA_FAIL_JMP;

            TempFunctionName.push_back(TempChar);

            if(TempChar == (CHAR)'\0')
                Done = TRUE;
        }

        if(TempFunctionName.find(lpProcName) != std::string::npos)
        {
            if(ExportFunctionTable[ExportOrdinalTable[i]] >= ExportDirectory.VirtualAddress &&
                ExportFunctionTable[ExportOrdinalTable[i]] <= ExportDirectory.VirtualAddress + ExportDirectory.Size)
            {
                Done = FALSE;
                std::string TempForwardString;
                TempForwardString.clear();

                for(UINT_PTR j = 0; !Done; ++j)
                {
                    /* Get next character */
                    if(!::ReadProcessMemory(hProcess,
                                             (LPCVOID)(RemoteModuleBaseVA + ExportFunctionTable[i] + j),
                                             &TempChar, sizeof(TempChar), NULL))
                        goto GRPA_FAIL_JMP;

                    TempForwardString.push_back(TempChar);

                    if(TempChar == (CHAR)'\0')
                        Done = TRUE;
                }
                size_t Dot = TempForwardString.find('.');
                if(Dot == std::string::npos)
                    goto GRPA_FAIL_JMP;

                std::string RealModuleName, RealFunctionId;
                RealModuleName = TempForwardString.substr(0, Dot);
                RealFunctionId = TempForwardString.substr(Dot + 1, std::string::npos);

                HMODULE RealModule = WinAPIExtended::getExternalModuleHandle(hProcess, RealModuleName.c_str());
                FARPROC TempReturn;

                if(RealFunctionId.at(0) == '#')
                {
                    UINT RealOrdinal = 0;
                    RealFunctionId.erase(0, 1);

                    for(size_t i = 0; i < RealFunctionId.size(); ++i)
                    {
                        if(RealFunctionId[i] >= '0' && RealFunctionId[i] <= '9')
                        {
                            RealOrdinal *= 10;
                            RealOrdinal += RealFunctionId[i] - '0';
                        }
                        else
                            break;
                    }

                    TempReturn = WinAPIExtended::getExternalProcAddress(hProcess, RealModule, NULL, RealOrdinal, TRUE);
                }
                else
                    TempReturn = WinAPIExtended::getExternalProcAddress(hProcess, RealModule, RealFunctionId.c_str(), 0, FALSE);

                delete[] ExportFunctionTable;
                delete[] ExportNameTable;
                delete[] ExportOrdinalTable;

                return TempReturn;
            }
            else
            {
                FARPROC TempReturn;
                TempReturn = (FARPROC)(RemoteModuleBaseVA + ExportFunctionTable[ExportOrdinalTable[i]]);

                delete[] ExportFunctionTable;
                delete[] ExportNameTable;
                delete[] ExportOrdinalTable;

                return TempReturn;
            }
        }
    }

    GRPA_FAIL_JMP:

        if(ExportFunctionTable != NULL)
            delete[] ExportFunctionTable;
        if(ExportNameTable != NULL)
            delete[] ExportNameTable;
        if(ExportOrdinalTable != NULL)
            delete[] ExportOrdinalTable;

        return NULL;
}

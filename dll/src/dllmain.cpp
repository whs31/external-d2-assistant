#include "networking/udpbase.hpp"
#include <Windows.h>
#include <iostream>
#include "dota/managers/interfacemanager.h"

#pragma comment(lib,"ws2_32.lib")

#define DLL_EXPORT extern "C" __declspec(dllexport)

uintptr_t WINAPI mainthread(HMODULE hModule) {
    AllocConsole();

    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "[STARTUP] Console allocated succesfully" << std::endl;
    UDP::UDPSocket::init()->start(9846);

    Global::InterfaceManager manager;
    manager.findInterfaces();

    while(true)
    {
        std::cout << UDP::UDPSocket::init()->receive().get();
    }

    std::cin.get();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                      )
{
    switch(ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH: {
            HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mainthread, hModule, 0, 0);
            if(thread)
                CloseHandle(thread);
            break;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }

    return 1;
}

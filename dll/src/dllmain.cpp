#include <Windows.h>
#include <iostream>

uintptr_t WINAPI mainthread(HMODULE hModule) {
    AllocConsole();

    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "[INFO] Console allocated succesfully" << std::endl;
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                      )
{
    switch (ul_reason_for_call)
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
    return TRUE;
}

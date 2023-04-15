#include <Windows.h>
#include <iostream>
#include "dota/managers/interfacemanager.h"

#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define DLL_EXPORT extern "C" __declspec(dllexport)

#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

DLL_EXPORT bool __stdcall attachTest()
{
    std::cout << "[DEBUG] Attach test called with sequence " << std::endl;
    return true;
}

void udpLoop(){
//    SOCKET s;
//    struct sockaddr_in server, si_other;
//    int slen , recv_len;
//    char buf[BUFLEN];
//    WSADATA wsa;

//    slen = sizeof(si_other) ;

//    //Initialise winsock
//    printf("\nInitialising Winsock...");
//    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
//    {
//        std::cout << "a" << std::endl;
//        return;
//    }
//    printf("Initialised.\n");

//    //Create a socket
//    if((s = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
//    {
//        std::cout << "b" << std::endl;
//        return;
//    }
//    printf("Socket created.\n");

//    //Prepare the sockaddr_in structure
//    server.sin_family = AF_INET;
//    server.sin_addr.s_addr = INADDR_ANY;
//    server.sin_port = htons( PORT );

//    //Bind
//    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
//    {
//        printf("Bind failed with error code : %d" , WSAGetLastError());
//        exit(EXIT_FAILURE);
//    }
//    puts("Bind done");

//    //keep listening for data
//    while(1)
//    {
//        printf("Waiting for data...");
//        fflush(stdout);

//        //clear the buffer by filling null, it might have previously received data
//        memset(buf,'\0', BUFLEN);

//        //try to receive some data, this is a blocking call
//        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
//        {
//            printf("recvfrom() failed with error code : %d" , WSAGetLastError());
//            exit(EXIT_FAILURE);
//        }
//        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
//        printf("Data: %s\n" , buf);
//    }

//    closesocket(s);
//    WSACleanup();


}

uintptr_t WINAPI mainthread(HMODULE hModule) {
    AllocConsole();

    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "[STARTUP] Console allocated succesfully" << std::endl;

    Global::InterfaceManager manager;
    manager.findInterfaces();
    udpLoop();

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

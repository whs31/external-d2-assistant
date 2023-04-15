#include "udpbase.hpp"



UdpBase::UdpBase()
{

}

UdpBase::~UdpBase()
{
    closesocket(m_socket);
    WSACleanup();
}

bool UdpBase::initInstance(const u_short _port)
{
    struct sockaddr_in server,  si_other;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");;
    server.sin_port = htons(_port);

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2), &m_wsaData) != 0)
    {
        std::cout << "a" << std::endl;
        return false;
    }
    printf("Initialised.\n");

    if((m_socket = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
    {
        std::cout << "b" << std::endl;
        return false;
    }
    printf("Socket created.\n");

    if( bind(m_socket ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        return false;
    }
    puts("Bind done");

    return true;
}



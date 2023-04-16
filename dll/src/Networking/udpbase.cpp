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

bool UdpBase::sendData(const DatagramHeader &_header, const DatagramData &_data, const sockaddr_in &_dstAddr){

    char * headerToSend = new char[sizeof(DatagramHeader) + 1]();
    memset(headerToSend, 0, sizeof(DatagramHeader) + 1);
    memcpy(headerToSend, &_header, sizeof(DatagramHeader));
    char * dataToSend = new char[_data.dataSize];
    memcpy(dataToSend, &_data.data, _data.dataSize);
    char * packageToSend = new char[sizeof(DatagramHeader) + _data.dataSize]();
    memcpy(packageToSend, headerToSend, sizeof(DatagramHeader) + 1);

    for (int i = 0; i < _data.dataSize; ++i)
    {
        packageToSend[sizeof(DatagramHeader) + i] = dataToSend[i];
    }

    if (sendto(m_socket, packageToSend, sizeof(DatagramHeader) + _data.dataSize, 0, (sockaddr*)&_dstAddr, sizeof(_dstAddr)) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d" , WSAGetLastError());
        return false;
    }
    return true;
}

std::unique_ptr<char[]> UdpBase::receiveData(){
    /// Наверное нужно добавить magicnumber в начало пакета, чтобы определять начало структуры
    DatagramHeader *receiveHeader  = new DatagramHeader();
    char  packageToReceive[MAXUINT16];
    if ((recvfrom(m_socket, packageToReceive, MAXUINT16, 0, (struct sockaddr *) nullptr, NULL)) == SOCKET_ERROR)
    {
        printf("recvfrom() failed with error code : %d" , WSAGetLastError());
        return nullptr;
    }

    std::unique_ptr<char[]> resultdata;
    memcpy(receiveHeader, packageToReceive, sizeof(DatagramHeader));

    if  (receiveHeader->messageSize != 0) {
        resultdata.reset(new char[receiveHeader->messageSize]());
        memcpy(resultdata.get(), packageToReceive +sizeof(DatagramHeader), receiveHeader->messageSize);
    }
    return std::move(resultdata);
}



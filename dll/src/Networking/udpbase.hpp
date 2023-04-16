#ifndef UDPBASE_HPP
#define UDPBASE_HPP

#include<winsock2.h>
#include <iostream>
#include <memory>

#include "ProtocolStructure.hpp"


///HOW TO
/// send

struct __attribute__((packed)) StructToSend {
    int a ;
    long long b;
}sendItem;

//sendItem.a = 17;
//sendItem.b = 1999199919991;

//UdpBase m_udp;
//m_udp.initInstance(9899);
//char a[] = "hello\0";
//DatagramHeader m_header;
//m_header.messageId = 1221;
//m_header.messageSize = sizeof(StructToSend);
//m_header.messageType = 9;
//struct sockaddr_in server;

//DatagramData m_data;
//m_data.dataSize = sizeof(StructToSend);
//m_data.data = new char[sizeof(StructToSend)]();
//memcpy(m_data.data,&sendItem,sizeof(StructToSend));


//server.sin_family = AF_INET;
//server.sin_addr.s_addr = inet_addr("127.0.0.1");;
//server.sin_port = htons(9898);
//m_udp.sendData(m_header, m_data , server);


///receive

//struct __attribute__((packed)) StructToReceive {
//    int a ;
//    long long b;
//}receiveItem;

//while(true){
//    auto result = m_udp.receiveData();
//    if (result != nullptr ) {
//        memcpy(&receiveItem, result.get(), sizeof(StructToReceive));
//         qDebug() <<ololo.a;
//         qDebug() <<ololo.b;
//    }
//}




class UdpBase
{
public:

    UdpBase();
    ~UdpBase();

    bool initInstance(const u_short _port = 9898);

    bool sendData(const DatagramHeader &_header, const DatagramData &_data , const struct sockaddr_in &_dstAddr);

    std::unique_ptr<char[]> receiveData();




private:
    WSADATA m_wsaData;
    SOCKET m_socket;
};

#endif // UDPBASE_HPP

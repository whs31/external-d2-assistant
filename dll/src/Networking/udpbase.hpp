#ifndef UDPBASE_HPP
#define UDPBASE_HPP

#include<winsock2.h>
#include <iostream>

#include "ProtocolStructure.hpp"

class UdpBase
{
public:


    UdpBase();
    ~UdpBase();

    bool initInstance(const u_short _port = 9898);

    template <typename T>
    bool sendData(const DatagramStructure<T> &_data, const struct sockaddr_in &_dstAddr){
        if (sendto(m_socket, &_data, sizeof(_data), 0, (sockaddr*)&_dstAddr, sizeof(_dstAddr)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d" , WSAGetLastError());
            return false;
        }
        return true;
    }

    template <typename T>
    DatagramStructure<T> receiveData(){
        DatagramStructure<T> receivedData;
        if ((recvfrom(m_socket, &receivedData, MAXUINT16, 0, (struct sockaddr *) nullptr, NULL)) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            return receivedData;
        }
        return receivedData;
    }




private:
    WSADATA m_wsaData;
    SOCKET m_socket;
};

#endif // UDPBASE_HPP

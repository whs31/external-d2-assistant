#pragma once

#include <winsock2.h>
#include <memory>
#include "datagram.hpp"

namespace UDP
{
    __struct_packed StructToSend
    {
        int a ;
        long long b;
    };

    class UDPSocket
    {
        WSADATA m_wsaData;
        SOCKET m_socket;

        public:
            static UDPSocket* init();
            ~UDPSocket();

            bool start(const u_short _port);

            bool send(const DatagramHeader &_header, const DatagramData &_data , const struct sockaddr_in &_dstAddr);

            std::unique_ptr<char[]> receive();

        private:
            static UDPSocket* instance;
            UDPSocket() = default;

    };
} // namespace UDP;

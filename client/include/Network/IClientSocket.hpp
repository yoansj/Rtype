/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** IClientSocket
*/

#ifndef ICLIENTSOCKET_HPP_
#define ICLIENTSOCKET_HPP_

#include "Bson.hpp"

#define NETCL_TCP_PORT (1234)           // Default TCP port
#define NETCL_UDP_PORT (7000)           // Default UDP port
#define NETCL_UDP_MAGIC (0x05BACE22)    // Magic number for UDP init packet
#define NETCL_DEFAULT_TIMEOUT (5000)    // Default timeout in ms

namespace Babel {
    namespace Network {
        class IClientSocket {
            public:
                virtual ~IClientSocket() = default;

                virtual void connectToAddr(std::string const &addr, int port = NETCL_TCP_PORT) = 0;
                virtual void disconnect() = 0;

                virtual void write(std::string const &packet) = 0;
                virtual std::string read() = 0;

                virtual void throwNetworkError(std::string const &err) = 0;
        };
    }
}

#endif /* !ICLIENTSocket_HPP_ */

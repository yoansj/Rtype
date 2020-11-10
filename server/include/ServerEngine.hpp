/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerEngine
*/

#ifndef SERVERENGINE_HPP_
#define SERVERENGINE_HPP_

#include <boost/asio.hpp>

#include "UdpServer.hpp"
#include "TcpHandler.hpp"

class ServerEngine {
    public:
        ServerEngine() = default;
        ~ServerEngine() = default;

        void serverLoop();

    private:
        UdpServer _udpServer;
        TcpHandler _tcpServer;
};

#endif /* !SERVERENGINE_HPP_ */

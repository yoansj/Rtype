/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include "Packages.hpp"
#include "EngineError.hpp"

#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>

class TcpClient {
    public:
        TcpClient(sf::IpAddress recipient, int port);
        ~TcpClient() = default;

        void sendPackage(void *package);
        std::size_t receivePackage(void);

    private:
        sf::TcpSocket _socket;
        sf::Socket::Status _status;
        sf::IpAddress _recipient;
        int _port;
        bool connected;
};

#endif /* !TCPCLIENT_HPP_ */

/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <SFML/Network.hpp>

class TcpClient {
    public:
        TcpClient(sf::IpAddress recipient, int port);
        ~TcpClient() = default;

        void sendPackage(void *package);
        void receivePackage(void);

    private:
        sf::TcpSocket _socket;
        sf::Socket::Status _status;
        sf::IpAddress _recipient;
        int _port;
};

#endif /* !TCPCLIENT_HPP_ */

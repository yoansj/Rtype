/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <SFML/Network.hpp>
#include <string>
#include "Packages.hpp"

class UdpClient {
    public:
        UdpClient(unsigned short port, sf::IpAddress recipient) {
            _port = port;
            _recipient = recipient;
        }

        void sendPackage(void const *package) {
            _socket.send(package, sizeof(connectionToServer_t), _recipient, _port);
        }

        std::string receivePackage(void) {
            char data[bufferSize];
            std::size_t received;
            sf::IpAddress sender;
            unsigned short port;

            _socket.receive(data, bufferSize, received, sender, port);
            return std::string(&data[0], received);
        }

    private:
        sf::UdpSocket _socket;
        sf::IpAddress _recipient;
        unsigned short _port;
};

#endif /* !UDPCLIENT_HPP_ */
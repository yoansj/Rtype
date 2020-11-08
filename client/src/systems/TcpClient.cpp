/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TcpClient
*/

#include <iostream>
#include "TcpClient.hpp"
#include "Packages.hpp"


TcpClient::TcpClient(sf::IpAddress recipient, int port) : _recipient(recipient), _port(port)
{
    _status = _socket.connect(_recipient, _port);
    if (_status != sf::Socket::Done)
        std::cerr << "uninitialized socket" << std::endl;
}

void TcpClient::sendPackage(void *package)
{
    if (_socket.send(package, bufferSize) != sf::Socket::Done)
        std::cerr << "package not send" << std::endl;
}

void TcpClient::receivePackage(void)
{
    char package[bufferSize];
    std::size_t received;

    if (_socket.receive(package, bufferSize, received) != sf::Socket::Done)
            std::cerr << "package not get" << std::endl;
}

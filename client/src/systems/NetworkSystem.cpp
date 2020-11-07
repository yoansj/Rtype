/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** NetworkSystem
*/

#include "NetworkSystem.hpp"


std::string Engine::NetworkSystem::receiveData()
{
    char data[bufferSize];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port;

    _serverSocket.receive(data, bufferSize, received, sender, port);
    return std::string(&data[0], received);
}

void Engine::NetworkSystem::send(void const *package)
{
    if (_serverSocket.send(package, sizeof(connectionToServer_t), _recipient, _port) != sf::Socket::Done) {
        throw EngineError("Network Error", "Package not sent !");
    }
}
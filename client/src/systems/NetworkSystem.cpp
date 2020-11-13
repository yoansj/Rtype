/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** NetworkSystem
*/

#include <cstring>
#include "NetworkSystem.hpp"
#include "Packages.hpp"
#include "PackagesType.hpp"

std::string Engine::NetworkSystem::receivePackage()
{
    char buffer[sizeof(int)];
    int typePackage;
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port;

    _socketUdp.receive(buffer, sizeof(int), received, sender, port);
    std::memcpy(&typePackage, buffer, sizeof(int));
    return std::string(&buffer[0], received);
}

void Engine::NetworkSystem::sendPackage(void const *package, int typePackage)
{
    switch (typePackage) {
    case CONNECTION_TO_SERVER:
        if (_socketUdp.send(package, sizeof(connectionToServer_t), _recipient, _port) != sf::Socket::Done) {
            throw EngineError("Network Error", "Package not sent !");
        }
        break;
    case CREATE_NEW_GAME:
        if (_socketTcp.send(package, sizeof(createNewGame_t)) != sf::Socket::Done) {
            throw EngineError("Network Error", "Package not sent !");
        }
        break;
    case POSITION_PACKAGE:
        if (_socketUdp.send(package, sizeof(position_t), _recipient, _port) != sf::Socket::Done) {
            throw EngineError("Network Error", "Package not sent !");
        }
    default:
        break;
    }
}
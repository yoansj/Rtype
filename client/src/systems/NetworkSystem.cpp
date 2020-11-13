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

template <class PkgType>
PkgType Engine::NetworkSystem::loadPkgType(bool typePackage, char *pkgUdp)
{
    PkgType pkg;
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port;

    if (typePackage == false)
        _socketTcp.receive(reinterpret_cast<char *>(&pkg) + sizeof(int), sizeof(PkgType) - sizeof(int), received);
    else
        std::memcpy(&pkg + sizeof(int), pkgUdp, sizeof(PkgType) - sizeof(int));
    return (pkg);
}


void Engine::NetworkSystem::receivePackageUdp()
{
    char buffer[4096];
    std::size_t received;
    int typePackage;
    sf::IpAddress sender;
    unsigned short port;

    _socketUdp.receive(buffer, 4096, received, sender, port);
    std::memcpy(&typePackage, &buffer, sizeof(int));
    switch (typePackage) {
    case PLAYERS_CONNECTED:
        auto pkg = loadPkgType<dataPlayersConnected_t>(true, reinterpret_cast<char *>(&buffer));
        std::cout << "On a reçu en UDP: " << pkg.type_struct << std::endl;
        break;
    }
}

void Engine::NetworkSystem::receivePackageTcp()
{
    char buffer[sizeof(int)];
    int typePackage;
    std::size_t received;

    _socketTcp.receive(buffer, sizeof(int), received);
    std::memcpy(&typePackage, buffer, sizeof(int));
    switch (typePackage) {
    case REPLY_GAME_CREATED:
        auto pkg = loadPkgType<replyGameCreated_t>(false, nullptr);
        setIdGame(pkg.idGame);
        break;
    }
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
    default:
        break;
    }
}
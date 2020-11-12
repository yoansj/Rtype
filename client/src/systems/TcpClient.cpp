/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TcpClient
*/

#include "TcpClient.hpp"

TcpClient::TcpClient(sf::IpAddress recipient, int port) : _recipient(recipient), _port(port), connected(false)
{
    _status = _socket.connect(_recipient, _port);
    // if (_status != sf::Socket::Done) {
    //     throw EngineError("Sockets error", "Couldn't connect to server");
    // }
    _socket.setBlocking(false);
    connected = true;
}

void TcpClient::sendPackage(void *package)
{
    if (_socket.send(package, bufferSize) != sf::Socket::Done)
        std::cerr << "package not send" << std::endl;
}

std::size_t TcpClient::receivePackage(void)
{
    if (!connected) return(42);

    char package[bufferSize];
    replyGameCreated_t reply;
    std::size_t received;

    if (_socket.receive(package, bufferSize, received) != sf::Socket::Done) {
        return (42);
    }
    std::memcpy(&reply, &package, sizeof(replyGameCreated_t));
    std::cout << "Game id: " << reply.idGame << std::endl;
    return reply.idGame;
}

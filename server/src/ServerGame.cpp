/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerGame
*/

#include "ServerGame.hpp"

void ServerGame::run()
{
    std::cout << "Starting lobby " << _gameId << " of owner: " << _creator->remote_endpoint().address() << ":" << _creator->remote_endpoint().port() << std::endl;

    while (1) {
        readPackages();
    }
}

void ServerGame::startGame()
{
    std::cout << "Starting game " << _gameId << " of owner: " << _creator->remote_endpoint().address() << ":" << _creator->remote_endpoint().port() << std::endl;
    gameStarted_t reply = {STARTED_GAME, "GAME STARTED"};

    for (std::size_t i = 0; i << _tcpPlayers.size(); i += 1) {
        _tcpPlayers.at(i)->send(boost::asio::buffer(&reply, sizeof(gameStarted_t)));
    }
    isOnLobby = false;
    isPlaying = true;
}

void ServerGame::readPackages()
{
    while (!_packages.empty()) {
        if (std::get<0>(_packages[0]) == POSITION_PACKAGE) {
            position_t package = *(position_t*)reinterpret_cast<char *>(std::get<1>(_packages[0]));
            std::cout << "Receive POSITION_PACKAGE from: " << package.senderIndex << std::endl;
        }
        _packages.erase(_packages.begin());
    }
}
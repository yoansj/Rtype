/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerGame
*/

#include "ServerGame.hpp"

void ServerGame::run()
{
    std::cout << "Starting game " << _gameId << "Of owner: " << _creator->remote_endpoint().address() << ":" << _creator->remote_endpoint().port() << std::endl;

    while (1) {
    }
}

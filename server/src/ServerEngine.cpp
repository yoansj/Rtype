/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerEngine
*/

#include "TcpHandler.hpp"
#include "ServerEngine.hpp"
#include "UdpServer.hpp"

void ServerEngine::serverLoop()
{
    while (1) {
        _tcpServer.run();
        // receive tcp
        // receive upd
        // vector de paquet
        // if paquet.gameId == id

    }
}
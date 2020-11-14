/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** main
*/

#include <boost/asio.hpp>
#include <thread>
#include "UdpServer.hpp"
#include "ServerEngine.hpp"

int main(int argc, char **argv)
{
    ServerEngine server;

    server.run();
    return 0;
}
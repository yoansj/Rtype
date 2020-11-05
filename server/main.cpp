/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** main
*/

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <memory>
#include "UdpServer.hpp"

// Connection -> Nombre de client connecté, la couleur (bleu/rouge/vert/jaune), vector Sprite joueur connecté
// Position joueurs & information joueur
// Position des monstres & information des monstres

int main(int argc, char **argv)
{
    try {
        boost::asio::io_service io_service;
        UdpServer server(io_service);
        std::thread thread1([&io_service]() { io_service.run(); });
        std::thread thread2([&io_service]() { io_service.run(); });
        thread1.join();
        thread2.join();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerEngine
*/

#include "TcpHandler.hpp"
#include "ServerEngine.hpp"
#include "UdpServer.hpp"
#include <memory>

void send_handler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        std::cout << "Donnée envoyée !" << std::endl;
    }
}

void accept_handler(std::shared_ptr<tcp::socket> &cli, const boost::system::error_code& error)
{
    if (!error) {
        replyGameCreated_t reply;
        reply = (replyGameCreated_t){REPLY_GAME_CREATED, 0, "REPLY_GAME_CREATED"};

        std::cout << "Nouveau client connexion acceptée !" << std::endl;
        cli->async_send(boost::asio::buffer(&reply, sizeof(reply)), send_handler);
    }
}

void ServerEngine::serverLoop()
{
    // boost::asio::io_service ios;

    // tcp::acceptor acceptor(ios, tcp::endpoint(tcp::v4(), 7172));

    // tcp::socket newClient(ios);
    // std::shared_ptr<tcp::socket> cli(std::make_shared<tcp::socket>(ios));

    std::cout << "Server start !" << std::endl;
    while (1) {
        //_tcpServer.run();
        // receive tcp
        // receive upd
        // vector de paquet
        // if paquet.gameId == id

        // acceptor.async_accept(*cli.get(), boost::bind(&accept_handler, cli, boost::asio::placeholders::error));

        _tcpManager.acceptConnections();
        _tcpManager.receivePackages();
        //ios.run();
    }
}
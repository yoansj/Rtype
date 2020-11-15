/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerEngine
*/

#ifndef ServerEngine_HPP_
#define ServerEngine_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <iostream>
#include <chrono>

#include "Packages.hpp"
#include "PackagesType.hpp"
#include "ServerGame.hpp"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

/**
 * @brief ServerEngine handle connection, receive and send package.
 * 
 */
class ServerEngine {
    public:
        /** typedef for std::shared_ptr<tcp::socket>
         */
        typedef std::shared_ptr<tcp::socket> tcpSocket;
        /** typedef for std::shared_ptr<udp::socket>
         */
        typedef std::shared_ptr<udp::socket> udpSocket;

        ServerEngine();
        ~ServerEngine() = default;

        // Tcp
        void acceptConnections();
        void receiveTcpPackages();
        void disconnectClients();

        // Server main loop
        void run();

        // Udp
        void receiveUdpPackages();

    private:
        void getPackageType(tcpSocket &cli, std::size_t index);

        template <class PkgType>
        PkgType loadPkgType(tcpSocket &cli);
        // Tcp package handlers
        void handlePackage(createNewGame_t &package, tcpSocket &cli);
        void handlePackage(startNewGame_t &package, tcpSocket &cli);
        void handlePackage(joinGame_t &package, tcpSocket &cli);

    private:
        // Boost asio service
        boost::asio::io_service _ios;

        // List of games
        std::map<std::size_t, std::shared_ptr<ServerGame>> _games;

        // Tcp Variables
        tcp::acceptor _acceptor;
        std::vector<tcpSocket> _clients;
        std::vector<std::size_t> _clientsToDisconnect;
        std::array<char, sizeof(int)> _buffer;

        // Udp Variables
        udp::socket _udpServer;
};

#endif /* !ServerEngine_HPP_ */

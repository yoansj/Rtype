/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TcpManager
*/

#ifndef TCPMANAGER_HPP_
#define TCPMANAGER_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <iostream>

#include "Packages.hpp"
#include "PackagesType.hpp"
#include "ServerGame.hpp"

using boost::asio::ip::tcp;

class TcpManager {
    public:
        typedef std::shared_ptr<tcp::socket> tcpSocket;

        TcpManager(boost::asio::io_service &service, std::vector<void *> &pkg, std::map<std::size_t, std::shared_ptr<ServerGame>> &games);
        ~TcpManager() = default;

        void acceptConnections();
        void receivePackages();

    private:
        void getPackageType(tcpSocket &cli, std::size_t index);

        template <class PkgType>
        PkgType loadPkgType(tcpSocket &cli);
        void handlePackage(createNewGame_t &package, tcpSocket &cli);
        void handlePackage(startNewGame_t &package, tcpSocket &cli);

    private:
        boost::asio::io_service &_ios;
        std::vector<void *> &_packagesList;
        tcp::acceptor _acceptor;

        std::map<std::size_t, std::shared_ptr<ServerGame>> &_games;

        std::vector<tcpSocket> _clients;
        std::array<char, sizeof(int)> _buffer;
};

#endif /* !TCPMANAGER_HPP_ */

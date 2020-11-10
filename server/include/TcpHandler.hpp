/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TcpHandler
*/

#ifndef TCPHANDLER_HPP_
#define TCPHANDLER_HPP_

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include "Packages.hpp"
#include "PackagesType.hpp"

using boost::asio::ip::tcp;

class TcpHandler
{
    public:
        TcpHandler() : _acceptor(_io_service, tcp::endpoint(tcp::v4(), 7171)) {};
        ~TcpHandler() = default;

        void run();
        void getTypePackage(void);
        void listNewGame(void);
        void createNewGame(int type_struct);
        void startNewGame(int type_struct);
        void acceptor(void);

    private:
        std::map<std::size_t, std::vector<tcp::endpoint>> _lobbyList;
        std::map<std::size_t, std::thread> _gameRunning;
        std::array<char, sizeof(int)> _buffer;
        std::vector<tcp::socket> _sockets;
        boost::asio::io_service _io_service;
        tcp::acceptor _acceptor;
};

#endif /* !TCPHANDLER_HPP_ */

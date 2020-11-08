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
#include "Packages.hpp"
#include "PackagesType.hpp"

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class TcpHandler
{
    public:
        TcpHandler() : _acceptor(_io_service, tcp::endpoint(tcp::v4(), 7171))
        {
        }
        ~TcpHandler() = default;

        void run() {
            while (1) {
                tcp::socket socket(_io_service);
                _acceptor.accept(socket);
                _sockets.push_back(std::move(socket));
                _sockets.back().receive(boost::asio::buffer(_buffer, bufferSize));
                getTypePackage();
                std::string message = make_daytime_string();
                boost::system::error_code ignored_error;
                boost::asio::write(_sockets.back(), boost::asio::buffer(message),
                                    boost::asio::transfer_all(), ignored_error);
            }
        }

        void getTypePackage(void) {
            int type_struct;

            std::memcpy(&type_struct, &_buffer, sizeof(int));
            if (type_struct == CREATE_NEW_GAME)
                createNewGame();
        }

        void createNewGame(void) {
            createNewGame_t package;

            std::memcpy(&package, &_buffer, sizeof(createNewGame_t));
            std::cout << package.message << std::endl;
        }
    private:
        std::array<char, bufferSize> _buffer;
        boost::asio::io_service _io_service;
        std::vector<tcp::socket> _sockets;
        tcp::acceptor _acceptor;
};

#endif /* !TCPHANDLER_HPP_ */

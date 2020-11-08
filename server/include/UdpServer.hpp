/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** UdpServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "PackagesType.hpp"
#include "Packages.hpp"

using boost::asio::ip::udp;

class UdpServer {
    public:
        UdpServer(boost::asio::io_service& io_service);

        void run(void);

        void send(std::string message);
        void print(void);
        void listNewGame(void);

    private:

        void startReceive();
        void handleReceive(const boost::system::error_code &error, std::size_t bytes);
        void handleSend(boost::shared_ptr<std::string> msg,
                            const boost::system::error_code & err,
                            std::size_t bytes);


        std::vector<int> players;
        std::map<std::size_t, std::thread> _listGameRuning;
        udp::socket _socket;
        udp::endpoint _remote_endpoint;
        std::array<char, bufferSize> _buffer;
};

#endif /* !UDPSERVER_HPP_ */

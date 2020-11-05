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
#include "Packages.hpp"

using boost::asio::ip::udp;

class UdpServer {
    public:
        UdpServer(boost::asio::io_service& io_service) : _socket(io_service, udp::endpoint(udp::v4(), 7171))
        {
            startReceive();
        }

        void send(std::string message)
        {
            _socket.send_to(boost::asio::buffer(message, message.size()), _remote_endpoint);
        }

    private:
        void startReceive() {
                _socket.async_receive_from(boost::asio::buffer(_buffer), _remote_endpoint,
                boost::bind(&UdpServer::handleReceive, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }

        void handleReceive(const boost::system::error_code &error, std::size_t bytes)
        {
            connectionToServer_t tmp;

            std::memcpy(&tmp, &_buffer, sizeof(connectionToServer_t));
            std::cout << tmp.message << std::endl;
            if (!error || error == boost::asio::error::message_size) {
                boost::shared_ptr<std::string> message(new std::string("100, 100"));
                _socket.async_send_to(boost::asio::buffer(*message), _remote_endpoint,
                                        boost::bind(&UdpServer::handleSend, this, message,
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
                startReceive();
            }
        }

        void handleSend(boost::shared_ptr<std::string> msg,
                            const boost::system::error_code & err,
                            std::size_t bytes)
        {
        }

        udp::socket _socket;
        udp::endpoint _remote_endpoint;
        std::array<char, bufferSize> _buffer;
};

#endif /* !UDPSERVER_HPP_ */

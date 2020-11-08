/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerEngine
*/

#ifndef SERVERENGINE_HPP_
#define SERVERENGINE_HPP_

#include <boost/asio.hpp>

#include "UdpServer.hpp"

class ServerEngine {
    public:
        ServerEngine() : server(io_service) {};
        ~ServerEngine() = default;

        void serverLoop();

    protected:
    private:
        boost::asio::io_service io_service;
        UdpServer server;
};

#endif /* !SERVERENGINE_HPP_ */

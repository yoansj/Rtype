/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerEngine
*/

#ifndef SERVERENGINE_HPP_
#define SERVERENGINE_HPP_

#include <boost/asio.hpp>
#include <map>
#include <memory>

#include "TcpManager.hpp"
#include "PackagesType.hpp"
#include "ServerGame.hpp"

class ServerEngine {
    public:
        ServerEngine() : _tcpManager(ios, _packagesList, _games) {};
        ~ServerEngine() = default;

        void serverLoop();

    private:
        boost::asio::io_service ios;
        std::vector<void *> _packagesList;

        std::map<std::size_t, std::shared_ptr<ServerGame>> _games;

        TcpManager _tcpManager;
};

#endif /* !SERVERENGINE_HPP_ */

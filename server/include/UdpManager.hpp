/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** UdpManager
*/

#ifndef UDPMANAGER_HPP_
#define UDPMANAGER_HPP_

#include <boost/asio.hpp>

#include "ServerGame.hpp"

using boost::asio::ip::udp;

class UdpManager {
    public:
        UdpManager(boost::asio::io_service &service, std::map<std::size_t, std::shared_ptr<ServerGame>> &games)
        : _ios(service), _games(games) {};
        ~UdpManager();

        void receivePackages();

    private:
        boost::asio::io_service &_ios;
        std::map<std::size_t, std::shared_ptr<ServerGame>> &_games;
};

#endif /* !UDPMANAGER_HPP_ */

/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerGame
*/

#ifndef SERVERGAME_HPP_
#define SERVERGAME_HPP_

#include "PackagesType.hpp"
#include "Packages.hpp"

#include <vector>
#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

typedef std::shared_ptr<udp::socket> udpSocket;
typedef std::shared_ptr<tcp::socket> tcpSocket;

class ServerGame {
    public:
        ServerGame(tcpSocket &creator, std::size_t id, udp::socket &serverSocket, boost::asio::io_service &service)
        : _creator(creator), _gameId(id), _udpServer(serverSocket), _ios(service) {};
        ~ServerGame() = default;

        void run();
        void startGame();
        void readPackages();
        void checkPlayers();

        void updateEndpoints(std::size_t index, udp::endpoint ep)
        {
            _playersEndpoints.insert({index, ep});
        }

        void addPackage(package const &pck) {_packages.push_back(pck);};

        std::size_t addPlayer(tcpSocket &p) {
            _tcpPlayers.push_back(p);
            std::cout << "Added player to game: " << _gameId << " Size: " << _tcpPlayers.size() << std::endl;
            return(_tcpPlayers.size() - 1);
        };

        std::size_t getId() const {return (_gameId);};

    private:
        std::vector<package> _packages;
        bool isOnLobby;
        bool isPlaying;
        tcpSocket _creator;
        std::size_t _gameId;
        udp::socket &_udpServer;
        boost::asio::io_service &_ios;
        std::vector<tcpSocket> _tcpPlayers;
        std::map<std::size_t, udp::endpoint> _playersEndpoints;
};

#endif /* !SERVERGAME_HPP_ */

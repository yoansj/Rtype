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
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
typedef std::shared_ptr<tcp::socket> tcpSocket;

class ServerGame {
    public:
        ServerGame(tcpSocket &creator, std::size_t id) : _creator(creator), _gameId(id) {};
        ~ServerGame() = default;

        void run();
        void startGame();
        void readPackages();
        void checkPlayers();

        void addPackage(std::tuple<PackagesType, void *> pck) {_packages.push_back(pck);};

        int addPlayer(tcpSocket &p) {
            _tcpPlayers.push_back(p);
            std::cout << "Added player to game: " << _gameId << " Size: " << _tcpPlayers.size() << std::endl;
            return(_tcpPlayers.size() - 1);
        };

        std::size_t getId() const {return (_gameId);};

    private:
        std::vector<std::tuple<PackagesType, void *>> _packages;
        bool isOnLobby;
        bool isPlaying;
        tcpSocket _creator;
        std::vector<tcpSocket> _tcpPlayers;
        std::size_t _gameId;
};

#endif /* !SERVERGAME_HPP_ */

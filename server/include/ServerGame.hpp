/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerGame
*/

#ifndef SERVERGAME_HPP_
#define SERVERGAME_HPP_

#include "System.hpp"
#include "ComponentManager.hpp"
#include "Component.hpp"
#include "PackagesType.hpp"
#include "Packages.hpp"
#include "Entity.hpp"
#include "PositionSystem.hpp"
#include "VelocitySystem.hpp"
#include "HitboxSystem.hpp"
#include "StatusSystem.hpp"
#include "MonsterLoaderSystem.hpp"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <boost/asio.hpp>
#include <chrono>
#include <filesystem>
#include <regex>

#define REGEX_MONSTERS "(\\./lib/lib)(.+)(\\.so)"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using monsterGenerator = Entity (*) (Engine::EntityManager &, Engine::PositionSystem &, Engine::VelocitySystem &, Engine::HitboxSystem &, Engine::StatusSystem &);

typedef std::shared_ptr<udp::socket> udpSocket;
typedef std::shared_ptr<tcp::socket> tcpSocket;

/**
 * @brief Clock class to manage the ServerGame part of the server.
 * 
 */
class Clock {
    public:
        Clock() : _t0(std::chrono::high_resolution_clock::now()), _t1(std::chrono::high_resolution_clock::now()) {};
        ~Clock() = default;
        void reset() { _t0 = std::chrono::high_resolution_clock::now(); _t1 = std::chrono::high_resolution_clock::now();}
        void setTime() {_t1 = std::chrono::high_resolution_clock::now();};
        int duration() const { return (std::chrono::duration_cast<std::chrono::milliseconds>( _t1 - _t0 ).count());};
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _t0;
        std::chrono::time_point<std::chrono::high_resolution_clock> _t1;
};

/**
 * @brief ServerGame managing all the parts launched by the clients.
 * 
 */
class ServerGame {
    public:
        /** @brief Constructor for the class ServerGame.
            @param param1 tcpSocket &creator
            @param param2 std::size_t id
            @param param3 udp::socket &serverSocket
            @param param4 boost::asio::io_service &service
        */
        ServerGame(tcpSocket &creator, std::size_t id, udp::socket &serverSocket, boost::asio::io_service &service)
        : _creator(creator), _gameId(id), _udpServer(serverSocket), _ios(service) {
            std::srand(std::time(nullptr));
            spawnTime = std::rand() % 10 + 1;
        };
        ~ServerGame() = default;

        void run();
        void startGame();
        void readPackages();
        void checkPlayers();
        void updateEntities();
        void spawnMonsters();

        void destroyEntities();

        /** Updates player sockets in the game.
            @param std::size_t index
            @param udp::endpoint ep
        */
        void updateEndpoints(std::size_t index, udp::endpoint ep)
        {
            _playersEndpoints.insert({index, ep});
        }

        /** Add a package to the game package list.
            @param package const &pck
        */
        void addPackage(package const &pck) {_packages.push_back(pck);};

        /** Add a player to the game
            @param tcpSocket &p
            @return std::size_t
        */
        std::size_t addPlayer(tcpSocket &p) {
            _tcpPlayers.push_back(p);
            std::cout << "Added player to game: " << _gameId << " Size: " << _tcpPlayers.size() << std::endl;
            return(_tcpPlayers.size() - 1);
        };

        /** Return the gameId
            @return std::size_t
        */
        std::size_t getId() const {return (_gameId);};

    private:

        //Tcp variables
        tcpSocket _creator;
        std::vector<tcpSocket> _tcpPlayers;

        //Udp variables
        udp::socket &_udpServer;
        std::map<std::size_t, udp::endpoint> _playersEndpoints;

        //Tcp & Udp
        std::vector<package> _packages;
        boost::asio::io_service &_ios;

        //Game variables
        bool isOnLobby;
        bool isPlaying;
        std::size_t _gameId;
        std::vector<std::size_t> _entitiesToDestroy;
        std::vector<Entity> _bulletEntities;
        std::vector<Entity> _ennemyEntities;
        std::vector<std::string> _libsToLoad;

        //Game utils
        Clock clock;
        Clock monstersClock;
        float spawnTime;
        Engine::EntityManager _entityManager;
        std::map<std::size_t, Entity> _players;
        Engine::PositionSystem _positionSystem;
        Engine::VelocitySystem _velocitySystem;
        Engine::HitboxSystem _hitboxSystem;
        Engine::StatusSystem _statusSystem;
        Engine::MonsterLoaderSystem _monsterLoaderSystem;
};

#endif /* !SERVERGAME_HPP_ */

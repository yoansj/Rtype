/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
#define NETWORKSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cstring>
#include <functional>

#include "Position.hpp"
#include "System.hpp"
#include "Packages.hpp"
#include "EngineError.hpp"
#include "SceneManager.hpp"
#include "PackagesType.hpp"

namespace Engine {

    /**
     * @brief  Network system used on the Position component
     */
    class NetworkSystem : public System<Position> {
        public:
            /**
             * @brief Construct a new Network System object
             * 
             */
            NetworkSystem() : System() {
                _recipient = "localhost";
                _port = 7172;
                _connectedTcp = true;
                _socketTcp.connect(_recipient, _port);
                _socketTcp.setBlocking(false);
                _socketUdp.setBlocking(false);
            };
            ~NetworkSystem() = default;

            /**
             * @brief sendPackage in UDP and TCP
             * 
             * @param char const *package 
             * @param int typePackage 
             */
            void sendPackage(char const *package, int typePackage);

            /**
             * @brief Set the Port variable
             * 
             * @param unsigned short port 
             */
            void setPort(unsigned short port) {_port = port;};

            /**
             * @brief Set the Recipient variable
             * 
             * @param sf::IpAddress recipient 
             */
            void setRecipient(sf::IpAddress recipient) {_recipient = recipient;};

            /**
             * @brief Set the Id Game variable
             * 
             * @param std::size_t idGame 
             */
            void setIdGame(std::size_t idGame) {_idGame = idGame;};

            /**
             * @brief Set the Player Index variable
             * 
             * @param std::size_t id 
             */
            void setPlayerIndex(std::size_t id) {_playerId = id;};

            /**
             * @brief Set the Destroy Lobby object
             * 
             * @param std::function<void()> f 
             */
            void setDestroyLobby(std::function<void()> f) {_destroyLobby = f;};

            /**
             * @brief Set the Game Update Player Pos object
             * 
             * @param std::function<void(std::size_t index, Position pos)> f 
             */
            void setGameUpdatePlayerPos(std::function<void(std::size_t index, Position pos)> f) {_gameUpdatePlayerPos = f;};

            /**
             * @brief Get the Id Game object
             * 
             * @return std::size_t 
             */
            std::size_t getIdGame() {return _idGame;};

            /**
             * @brief Get the Player Id object
             * 
             * @return std::size_t 
             */
            std::size_t getPlayerId() {return _playerId;};

            /**
             * @brief Get the Player Nb object
             * 
             * @return int 
             */
            int getPlayerNb() {return _playerNb;}


            /**
             * @brief Update NetworkSystem Component
             * 
             * @param SceneManager &smgr 
             * @param EntityManager &entityManager 
             */
            void update(SceneManager &smgr, EntityManager &entityManager) {
                receivePackageUdp();
                receivePackageTcp(smgr, entityManager);
            };

            /**
             * @brief receive Package in UDP and disptach them.
             * 
             */
            void receivePackageUdp();

            /**
             * @brief receive Package in TCP and disptach them.
             * 
             * @param SceneManager &smgr 
             * @param EntityManager &entityManager 
             */
            void receivePackageTcp(SceneManager &smgr, EntityManager &entityManager);

            /**
             * @brief Load and charge a package.
             * 
             * @tparam PkgType 
             * @param bool typePackage 
             * @param char *pkgUdp 
             * @return PkgType 
             */
            template <class PkgType>
            PkgType loadPkgType(bool typePackage, char *pkgUdp);
        private:
            // Ip and port of server
            sf::IpAddress _recipient;
            unsigned short _port;

            // Sockets
            sf::UdpSocket _socketUdp;
            sf::TcpSocket _socketTcp;

            // Game variables
            std::size_t _idGame;
            std::size_t _playerId;
            int _playerNb;

            // Misc
            bool _connectedTcp;
            std::function<void()> _destroyLobby;
            std::function<void(std::size_t index, Position pos)> _gameUpdatePlayerPos;
    };

}

#endif /* !NETWORKSYSTEM_HPP_ */

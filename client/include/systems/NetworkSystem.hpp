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
     * @brief  Position system used on the Position component
     */
    class NetworkSystem : public System<Position> {
        public:
            NetworkSystem() : System() {
                _recipient = "localhost";
                _port = 7172;
                _connectedTcp = true;
                _socketTcp.connect(_recipient, _port);
                _socketTcp.setBlocking(false);
                _socketUdp.setBlocking(false);
            };
            ~NetworkSystem() = default;

            void sendPackage(char const *package, int typePackage);

            void setPort(unsigned short port) {_port = port;};
            void setRecipient(sf::IpAddress recipient) {_recipient = recipient;};
            void setIdGame(std::size_t idGame) {_idGame = idGame;};
            void setPlayerIndex(std::size_t id) {_playerId = id;};

            void setDestroyLobby(std::function<void()> f) {_destroyLobby = f;};

            std::size_t getIdGame() {return _idGame;};
            std::size_t getPlayerId() {return _playerId;};
            int getPlayerNb() {return _playerNb;}

            void update(SceneManager &smgr, EntityManager &entityManager) {
                receivePackageUdp();
                receivePackageTcp(smgr, entityManager);
            };

            void receivePackageUdp();
            void receivePackageTcp(SceneManager &smgr, EntityManager &entityManager);
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
    };

}

#endif /* !NETWORKSYSTEM_HPP_ */

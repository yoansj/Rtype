/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerGame
*/

#include "ServerGame.hpp"

/** Launch loop, call the functions necessary to read packets.
*/
void ServerGame::run()
{
    std::cout << "Starting lobby " << _gameId << " of owner: " << _creator->remote_endpoint().address() << ":" << _creator->remote_endpoint().port() << std::endl;

    while (1) {
        //boost::asio::deadline_timer t(_ios, boost::posix_time::seconds(1000 / 60));
        //t.wait();
        //std::cout << "CLOCK" << std::endl;
        readPackages();
    }
}

void ServerGame::checkPlayers()
{
}

/** Starts the game and sends all connected clients a packet informing them that the game has started.
*/
void ServerGame::startGame()
{
    //std::cout << "Starting game " << _gameId << " of owner: " << _creator->remote_endpoint().address() << ":" << _creator->remote_endpoint().port() << std::endl;
    gameStarted_t reply = {STARTED_GAME, _tcpPlayers.size(), "GAME STARTED"};

    for (std::size_t i = 0; i != _tcpPlayers.size(); i += 1) {
        std::cout << "[" << _gameId << "] Sending start package " << std::endl;
        _tcpPlayers[i]->send(boost::asio::buffer(&reply, sizeof(gameStarted_t)));
    }
    isOnLobby = false;
    isPlaying = true;
}

/** Read the packets and act accordingly according to the received packet.
*/
void ServerGame::readPackages()
{
    while (!_packages.empty()) {
        if (_packages[0].type == POSITION_PACKAGE) {
            // Recevoir le paquet position
            // Renvoyer la position a tout le monde sauf a l'envoyeur du paquet
            // Insérer l'endpoint dans la liste des endpoints

            // Paquet reçu
            position_t *package = reinterpret_cast<position_t *>(_packages[0].package);
            // Update les endpoint
            updateEndpoints(package->senderIndex, _packages[0].endpoint);

            std::cout << "[" << _gameId << "] Receive POSITION_PACKAGE from: " << _packages[0].endpoint.address() << ":" << _packages[0].endpoint.port() << std::endl;

            // Code d'erreur (inutilisé et endpoint)
            boost::system::error_code error;
            for (int i = 0; i != _tcpPlayers.size(); i++) {
                std::cout << "Send position package SenderIndex: " << package->senderIndex << std::endl;
                auto endpoint = _playersEndpoints.find(i);
                if (endpoint != _playersEndpoints.end())
                    _udpServer.send_to(boost::asio::buffer(reinterpret_cast<char *>(package), sizeof(position_t)), endpoint->second, 0, error);
            }
        }
        if (_packages[0].type == SHOOT_PACKAGE) {
            // Crée l'entité bullet
            // Set position de l'entité devant le vaisseau

            // Paquet reçu
            shoot_t *package = reinterpret_cast<shoot_t *>(_packages[0].package);
            Entity bullet = _entityManager.create();
            _positionSystem.create(bullet);
            _velocitySystem.create(bullet);
            _velocitySystem.setVelocity(bullet, 20, 0);
            _positionSystem.setPosition(bullet, package->pos.x + 20, package->pos.y);

            std::cout << "[" << _gameId << "] Receive SHOOT_PACKAGE from: " << _packages[0].endpoint.address() << ":" << _packages[0].endpoint.port() << std::endl;

            _serverEntities.push_back(bullet);
        }
        _packages.erase(_packages.begin());
    }
}
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

    clock.reset();
    monstersClock.reset();
    while (1) {
        readPackages();
        clock.setTime();
        monstersClock.setTime();
        if (clock.duration() >= 1000.0 / 60.0) {
            updateEntities();
            clock.reset();
        }
        if (isPlaying)
            spawnMonsters();
    }
}

void ServerGame::checkPlayers()
{
}

void ServerGame::checkCollisions()
{
    //for (std::size_t i = 0; )
}

void ServerGame::spawnMonsters()
{
    if (monstersClock.duration() >= 5 * 1000) {
        std::cout << "Spawn monster" << std::endl;
        //monsterGenerator frogFactory = reinterpret_cast<monsterGenerator>(_monsterLoaderSystem.getFactory(0));
        //auto frog = frogFactory(_entityManager, _positionSystem, _velocitySystem, _hitboxSystem, _statusSystem);
        auto frog = _entityManager.create();
        _positionSystem.create(frog);
        _velocitySystem.create(frog);
        _velocitySystem.setVelocity(frog, -10, 0);
        _hitboxSystem.create(frog);
        _hitboxSystem.setHitbox(frog, 70, 30, Engine::HitboxType::MONSTER);
        _statusSystem.create(frog);
        _statusSystem.setStatus(frog, Engine::ALIVE);
        _positionSystem.setPosition(frog, std::rand() % 2000 + 1900,  std::rand() % 900 + 100);
        _ennemyEntities.push_back(frog);
        monstersClock.reset();
    }
}

/** Starts the game and sends all connected clients a packet informing them that the game has started.
*/
void ServerGame::updateEntities()
{
    // Update des balles
    for (std::size_t i = 0; i != _bulletEntities.size(); i++) {
        if (!_positionSystem.Exist(_bulletEntities[i])) continue;
        auto &bulletPos = _positionSystem.getComponent(_bulletEntities[i]);
        auto &bulletVel = _velocitySystem.getComponent(_bulletEntities[i]);
        auto &bulletStatus = _statusSystem.getComponent(_bulletEntities[i]);

        bulletPos.x += bulletVel.x;
        bulletPos.y += bulletVel.y;

        if (bulletPos.x >= 2000) {
            bulletStatus.type = Engine::DEAD;
            std::cout << "Bullet is outside of the screen !" << std::endl;
        }
        shootEntity_t package = {
            SHOOT_ENTITY_PACKAGE,
            bulletPos,
            _hitboxSystem.getComponent(_bulletEntities[i]),
            bulletStatus,
            _bulletEntities[i]
        };

        boost::system::error_code error;
        for (int i = 0; i != _tcpPlayers.size(); i++) {
            auto endpoint = _playersEndpoints.find(i);
            if (endpoint != _playersEndpoints.end())
                _udpServer.send_to(boost::asio::buffer(reinterpret_cast<char *>(&package), sizeof(shootEntity_t)), endpoint->second, 0, error);
        }
        if (bulletStatus.type == Engine::DEAD) {
            std::cout << "Destroying components of bullet !" << std::endl;
            _positionSystem.destroy(_bulletEntities[i]);
            _velocitySystem.destroy(_bulletEntities[i]);
            _hitboxSystem.destroy(_bulletEntities[i]);
            _statusSystem.destroy(_bulletEntities[i]);
            _entitiesToDestroy.push_back(i);
        }
    }
    // Update des monstres
    for (std::size_t i = 0; i != _ennemyEntities.size(); i++) {
        if (!_positionSystem.Exist(_ennemyEntities[i])) continue;
        auto &monsterPos = _positionSystem.getComponent(_ennemyEntities[i]);
        auto &monsterVel = _velocitySystem.getComponent(_ennemyEntities[i]);
        auto &monsterStatus = _statusSystem.getComponent(_ennemyEntities[i]);

        monsterPos.x += monsterVel.x;
        monsterPos.y += monsterVel.y;

        if (monsterPos.x <= -100) {
            monsterStatus.type = Engine::DEAD;
            std::cout << "Monster is outside of the screen !" << std::endl;
        }

        monsterEntity_t package = {
            MONSTER_ENTITY_PACKAGE,
            monsterPos,
            monsterStatus,
            _ennemyEntities[i],
            //_monsterLoaderSystem.getFilepath(0)[0]
            "../client/assets/monster.png"
        };

        boost::system::error_code error;
        for (int i = 0; i != _tcpPlayers.size(); i++) {
            auto endpoint = _playersEndpoints.find(i);
            if (endpoint != _playersEndpoints.end())
                _udpServer.send_to(boost::asio::buffer(reinterpret_cast<char *>(&package), sizeof(monsterEntity_t)), endpoint->second, 0, error);
        }
        if (monsterStatus.type == Engine::DEAD) {
            std::cout << "Destroying components of monster !" << std::endl;
            _positionSystem.destroy(_ennemyEntities[i]);
            _velocitySystem.destroy(_ennemyEntities[i]);
            _hitboxSystem.destroy(_ennemyEntities[i]);
            _statusSystem.destroy(_ennemyEntities[i]);
            //_entitiesToDestroy.push_back(i);
        }
    }
    destroyEntities();
}

void ServerGame::destroyEntities()
{
    for (std::size_t i = 0; i != _entitiesToDestroy.size(); i++) {
        if (std::find(_bulletEntities.begin(), _bulletEntities.end(), _entitiesToDestroy[i]) != _bulletEntities.end())
            _bulletEntities.erase(_bulletEntities.begin() + _entitiesToDestroy[i]);
    }
    _entitiesToDestroy.clear();
}

/** Start the game and send a packet to all the clients to signal it, create a player entity and set all the data necessary for its operation.
*/
void ServerGame::startGame()
{
    std::cout << "Starting game " << _gameId << " of owner: " << _creator->remote_endpoint().address() << ":" << _creator->remote_endpoint().port() << std::endl;
    gameStarted_t reply = {STARTED_GAME, _tcpPlayers.size(), "GAME STARTED"};

    /*std::string path = "./lib";
    std::smatch m;

    for (auto const &e : std::filesystem::directory_iterator(path)) {
        std::string path = e.path.string();
        if (std::regex_search(path, m, std::basic_regex<char>(REGEX_MONSTERS))) {
            std::cout << m[2] << std::endl;
        }
    }*/

    /*_monsterLoaderSystem.load({
        "libs/libfrog.so"
    });*/

    for (std::size_t i = 0; i != _tcpPlayers.size(); i += 1) {
        std::cout << "[" << _gameId << "] Sending start package " << std::endl;
        _tcpPlayers[i]->send(boost::asio::buffer(&reply, sizeof(gameStarted_t)));

        // Create player entity
        Entity player = _entityManager.create();
        _positionSystem.create(player);
        _hitboxSystem.create(player);
        _hitboxSystem.setHitbox(player, 32, 100, Engine::HitboxType::PLAYER);
        _players.insert({i, player});
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

            // Update la position du joueur dans les entités
            auto playerEntity = _players.find(package->senderIndex);
            if (playerEntity != _players.end()) {
                auto &playerPos = _positionSystem.getComponent(playerEntity->second);
                playerPos.x = package->pos.x;
                playerPos.y = package->pos.y;
            }
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

            // Créer une entité bullet
            // Elle sapwn a la position du joueur + 20 en avant
            // Hitbox de 32 x 32
            Entity bullet = _entityManager.create();
            // Créer les composants
            _positionSystem.create(bullet);
            _velocitySystem.create(bullet);
            _hitboxSystem.create(bullet);
            _statusSystem.create(bullet);
            // Les initialiser
            _hitboxSystem.setHitbox(bullet, 32, 32, Engine::HitboxType::BULLET);
            _velocitySystem.setVelocity(bullet, 20, 0);
            _positionSystem.setPosition(bullet, package->pos.x + 10, package->pos.y);
            _statusSystem.setStatus(bullet, Engine::ALIVE);
            // Ajouter la balle dans la liste des balles
            _bulletEntities.push_back(bullet);

            std::cout << "[" << _gameId << "] Receive SHOOT_PACKAGE from: " << _packages[0].endpoint.address() << ":" << _packages[0].endpoint.port() << std::endl;
        }
        _packages.erase(_packages.begin());
    }
}
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
    for (std::size_t i = 0; _bulletEntities.size(); i++) {
        for (std::size_t m = 0; m != _ennemyEntities.size(); m++) {
            std::cout << i << " and " << m << std::endl;
            /*if (!_hitboxSystem.Exist(_bulletEntities[i]) || !_hitboxSystem.Exist(_ennemyEntities[m])) continue;
            if (_hitboxSystem.collides(_bulletEntities[i], _positionSystem.getComponent(_bulletEntities[i]),
            _ennemyEntities[m], _positionSystem.getComponent(_ennemyEntities[m]))) {
                std::cout << "collision !!!" << std::endl;
                if (!_statusSystem.Exist(_bulletEntities[i]) || !_statusSystem.Exist(_ennemyEntities[m])) continue;
                _statusSystem.setStatus(_bulletEntities[i], Engine::DEAD);
                _statusSystem.setStatus(_ennemyEntities[i], Engine::DEAD);
            }*/
        }
    }
}

void ServerGame::spawnMonsters()
{
    if (monstersClock.duration() >= 5 * 1000) {
        //monsterGenerator frogFactory = reinterpret_cast<monsterGenerator>(_monsterLoaderSystem.getFactory(0));
        //auto frog = frogFactory(_entityManager, _positionSystem, _velocitySystem, _hitboxSystem, _statusSystem);
        auto frog = _entityManager.create();
        std::cout << "Spawn monster ENTITY: " << frog << std::endl;
        _positionSystem.create(frog);
        _velocitySystem.create(frog);
        _hitboxSystem.create(frog);
        _statusSystem.create(frog);

        _positionSystem.setPosition(frog, std::rand() % 2000 + 1900,  std::rand() % 900 + 100);
        _velocitySystem.setVelocity(frog, -10, 0);
        _hitboxSystem.setHitbox(frog, 70, 30, Engine::HitboxType::MONSTER);
        _statusSystem.setStatus(frog, Engine::ALIVE);
        _ennemyEntities.push_back(frog);
        monstersClock.reset();
    }
}

void ServerGame::iterateForCollision(Entity e, Engine::Position &pos, Engine::Status &status)
{
    for (std::size_t i = 0; i != _ennemyEntities.size(); i++) {
        //std::cout << "Bullet id is: " << e << " Ennemy id is: " << _ennemyEntities[i] << std::endl;
        if (!_statusSystem.Exist(_ennemyEntities[i])) continue; // Si l'ennemi a pas de status on skip
        if (status.type == Engine::DEAD || _statusSystem.getComponent(_ennemyEntities[i]).type == Engine::DEAD) continue; //Si un des deux est mort on skip
        if (_hitboxSystem.collides(e, pos, _ennemyEntities[i], _positionSystem.getComponent(_ennemyEntities[i])) == true) {
            std::cout << "collision !!!" << std::endl;
            _statusSystem.setStatus(_ennemyEntities[i], Engine::DEAD);
            _statusSystem.setStatus(e, Engine::DEAD);
        }
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

        iterateForCollision(_bulletEntities[i], bulletPos, bulletStatus);

        if (bulletStatus.type == Engine::DEAD) {
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
            _positionSystem.destroy(_ennemyEntities[i]);
            _velocitySystem.destroy(_ennemyEntities[i]);
            _hitboxSystem.destroy(_ennemyEntities[i]);
            _statusSystem.destroy(_ennemyEntities[i]);
            _ennemiesToDestroy.push_back(i);
            std::cout << "ERASED MONSTER : " << _ennemyEntities[i] << std::endl;
        }
    }
}

void ServerGame::destroyEntities()
{
    for (std::size_t i = 0; i != _entitiesToDestroy.size(); i++) {
        if (std::find(_bulletEntities.begin(), _bulletEntities.end(), _entitiesToDestroy[i]) != _bulletEntities.end())
            _bulletEntities.erase(_bulletEntities.begin() + _entitiesToDestroy[i]);
    }
    _entitiesToDestroy.clear();
    for (std::size_t i = 0; i != _ennemiesToDestroy.size(); i++) {
        if (std::find(_ennemyEntities.begin(), _ennemyEntities.end(), _ennemiesToDestroy[i]) != _ennemyEntities.end())
            _ennemyEntities.erase(_ennemyEntities.begin() + _entitiesToDestroy[i]);
    }
    _ennemiesToDestroy.clear();
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

            //std::cout << "[" << _gameId << "] Receive POSITION_PACKAGE from: " << _packages[0].endpoint.address() << ":" << _packages[0].endpoint.port() << std::endl;

            // Update la position du joueur dans les entités
            auto playerEntity = _players.find(package->senderIndex);
            if (playerEntity != _players.end()) {
                auto &playerPos = _positionSystem.getComponent(playerEntity->second);
                playerPos.x = package->pos.x;
                playerPos.y = package->pos.y;
            }
            boost::system::error_code error;
            for (int i = 0; i != _tcpPlayers.size(); i++) {
                //std::cout << "Send position package SenderIndex: " << package->senderIndex << std::endl;
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
            _hitboxSystem.setHitbox(bullet, 35, 15, Engine::HitboxType::BULLET);
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
/*
[COLLIDES] A.x: 50 A.y: 540 B.x: 710 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 70 A.y: 540 B.x: 700 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 90 A.y: 540 B.x: 690 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 110 A.y: 540 B.x: 680 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 130 A.y: 540 B.x: 670 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 150 A.y: 540 B.x: 660 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 170 A.y: 540 B.x: 650 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 190 A.y: 540 B.x: 640 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 210 A.y: 540 B.x: 630 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 230 A.y: 540 B.x: 620 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 250 A.y: 540 B.x: 610 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 270 A.y: 540 B.x: 600 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 290 A.y: 540 B.x: 590 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 310 A.y: 540 B.x: 580 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 330 A.y: 540 B.x: 570 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 350 A.y: 540 B.x: 560 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 370 A.y: 540 B.x: 550 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 390 A.y: 540 B.x: 540 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 410 A.y: 540 B.x: 530 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 430 A.y: 540 B.x: 520 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 450 A.y: 540 B.x: 510 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 470 A.y: 540 B.x: 500 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 490 A.y: 540 B.x: 490 B.y: 561 <---------------------------
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30 <----------------------
[COLLIDES] A.x: 510 A.y: 540 B.x: 480 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 530 A.y: 540 B.x: 470 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 550 A.y: 540 B.x: 460 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 570 A.y: 540 B.x: 450 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 590 A.y: 540 B.x: 440 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 610 A.y: 540 B.x: 430 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 630 A.y: 540 B.x: 420 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 650 A.y: 540 B.x: 410 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 670 A.y: 540 B.x: 400 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 690 A.y: 540 B.x: 390 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 710 A.y: 540 B.x: 380 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 730 A.y: 540 B.x: 370 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 750 A.y: 540 B.x: 360 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 770 A.y: 540 B.x: 350 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 790 A.y: 540 B.x: 340 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
[COLLIDES] A.x: 810 A.y: 540 B.x: 330 B.y: 561
[COLLIDES] Ahitbox.x: 3000 Ahitbox.y: 3000 Bhitbox.x: 70 Bhitbox.y: 30
*/
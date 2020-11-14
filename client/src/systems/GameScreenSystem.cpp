/*
** EPITECH PROJECT, 2020
** client
** File description:
** GameScreenSystem
*/

#include "GameScreenSystem.hpp"

void Engine::GameScreenSystem::createSprites(std::array<Entity, 2> parallax)
{
    _spriteSystem.create(parallax[0]);
    _positionSystem.create(parallax[0]);
    _positionSystem.setPosition(parallax[0], 0, 0);
    _spriteSystem.initSprite(parallax[0], "../client/assets/parallax.png", false);
    _velocitySystem.create(parallax[0]);
    _velocitySystem.setVelocity(parallax[0], 3, 3);
    _parallaxSystem.setBackgroundEntity(parallax[0]);

    _spriteSystem.create(parallax[1]);
    _positionSystem.create(parallax[1]);
    _positionSystem.setPosition(parallax[1], 3840, 0);
    _spriteSystem.initSprite(parallax[1], "../client/assets/parallax.png", false);
    _velocitySystem.create(parallax[1]);
    _velocitySystem.setVelocity(parallax[1], 3, 3);
    _parallaxSystem.setBackgroundEntity(parallax[1]);


    _gameScreenEntities.push_back(parallax[0]);
    _gameScreenEntities.push_back(parallax[1]);
    _created = true;
    initGame();
}

void Engine::GameScreenSystem::initGame()
{
    for (int i = 0; i != _getPlayerNb(); i++) {
        if (i == 0) {
            Entity p = _createEntity();
            _spriteSystem.create(p);
            _positionSystem.create(p);
            _velocitySystem.create(p);
            _spriteSystem.initSprite(p, "../client/assets/bluePlayer.png", false);
            _spriteSystem.setScale(p, 4, 4);
            // _spriteSystem.setRect(p, sf::IntRect(67, 0, 32, 100));
            _positionSystem.setPosition(p, 20, 150);
            _velocitySystem.setVelocity(p, 10, 10);
            _playerEntities.push_back(p);
        }
        if (i == 1) {
            Entity p = _createEntity();
            _spriteSystem.create(p);
            _positionSystem.create(p);
            _velocitySystem.create(p);
            _spriteSystem.initSprite(p, "../client/assets/redPlayer.png", true);
            _spriteSystem.setScale(p, 4, 4);
            _spriteSystem.setRect(p, sf::IntRect(67, 0, 32, 100));
            _positionSystem.setPosition(p, 20, 300);
            _velocitySystem.setVelocity(p, 10, 10);
            _playerEntities.push_back(p);
        }
        if (i == 2) {
            Entity p = _createEntity();
            _spriteSystem.create(p);
            _positionSystem.create(p);
            _velocitySystem.create(p);
            _spriteSystem.initSprite(p, "../client/assets/greenPlayer.png", true);
            _spriteSystem.setScale(p, 4, 4);
            _spriteSystem.setRect(p, sf::IntRect(67, 0, 32, 100));
            _positionSystem.setPosition(p, 20, 450);
            _velocitySystem.setVelocity(p, 10, 10);
            _playerEntities.push_back(p);
        }
        if (i == 3) {
            Entity p = _createEntity();
            _spriteSystem.create(p);
            _positionSystem.create(p);
            _velocitySystem.create(p);
            _spriteSystem.initSprite(p, "../client/assets/yellowPlayer.png", true);
            _spriteSystem.setScale(p, 4, 4);
            _spriteSystem.setRect(p, sf::IntRect(67, 0, 32, 100));
            _positionSystem.setPosition(p, 20, 600);
            _velocitySystem.setVelocity(p, 10, 10);
            _playerEntities.push_back(p);
        }
    }
    _createdAllPlayers = true;
}

void Engine::GameScreenSystem::destroySprites(EntityManager &entityManager)
{
    for (int i = 0; i != _gameScreenEntities.size(); i++) {
        _spriteSystem.destroy(_gameScreenEntities[i]);
        _velocitySystem.destroy(_gameScreenEntities[i]);
        _positionSystem.destroy(_gameScreenEntities[i]);
        //_parallaxSystem.destroy(_gameScreenEntities[i]);
        entityManager.remove(_gameScreenEntities[i]);
    }
    _created = false;
}

void Engine::GameScreenSystem::updatePlayerPosition(std::size_t index, Position pos)
{
    if (_getPlayerId() != index && _createdAllPlayers) {
        auto &playerPosition = _positionSystem.getComponent(_playerEntities[index]);

        playerPosition.x = pos.x;
        playerPosition.y = pos.y;
    }
}

void Engine::GameScreenSystem::update(EntityManager &entityManager, SceneManager &sceneManager)
{
    _parallaxSystem.update(_positionSystem.getComponent(_gameScreenEntities[0]), _velocitySystem.getComponent(_gameScreenEntities[0]));
    _parallaxSystem.update(_positionSystem.getComponent(_gameScreenEntities[1]), _velocitySystem.getComponent(_gameScreenEntities[1]));

    if (_createdAllPlayers) {
        auto &playerPosition = _positionSystem.getComponent(_playerEntities[_getPlayerId()]);
        auto &playerVelocity = _velocitySystem.getComponent(_playerEntities[_getPlayerId()]);
        auto &playerSprite = _spriteSystem.getComponent(_playerEntities[_getPlayerId()]);

        if (_hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerPosition.x -= playerVelocity.x;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerPosition.x += playerVelocity.x;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                playerPosition.y -= playerVelocity.y;
                playerSprite.rect.left = 320;
                playerSprite.rect.width = 152;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                playerPosition.y += playerVelocity.y;
                playerSprite.rect.left = 0;
                playerSprite.rect.width = 160;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                // Envoyer un paquet shoot
                shoot_t package = {SHOOT_PACKAGE, _getPlayerId(), _getGameId(), playerPosition};
                _sendPackage(reinterpret_cast<char *>(&package), SHOOT_PACKAGE);
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                playerSprite.rect.left = 170;
                playerSprite.rect.width = 148;
            }
        }
        position_t package = {POSITION_PACKAGE, _getPlayerId(), _getGameId(), playerPosition};
        _sendPackage(reinterpret_cast<char *>(&package), POSITION_PACKAGE);
    }
}
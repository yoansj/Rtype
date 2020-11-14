/*
** EPITECH PROJECT, 2020
** client
** File description:
** JoinScreenSystem
*/


#include "JoinScreenSystem.hpp"

void Engine::JoinScreenSystem::createSprites(std::array<Entity, 2> parallax, std::array<Entity, 3> buttons, Entity text)
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
    _positionSystem.setPosition(parallax[1], 1920, 0);
    _spriteSystem.initSprite(parallax[1], "../client/assets/parallax.png", false);
    _velocitySystem.create(parallax[1]);
    _velocitySystem.setVelocity(parallax[1], 3, 3);
    _parallaxSystem.setBackgroundEntity(parallax[1]);

    // _spriteSystem.create(buttons[1]);
    // _positionSystem.create(buttons[1]);
    // _positionSystem.setPosition(buttons[1], 700, 400);
    // _spriteSystem.initSprite(buttons[1], "../client/assets/join.png", false);
    // _spriteSystem.setScale(buttons[1], 2, 2);

    // _spriteSystem.create(buttons[2]);
    // _positionSystem.create(buttons[2]);
    // _positionSystem.setPosition(buttons[2], 700, 600);
    // _spriteSystem.initSprite(buttons[2], "../client/assets/quit.png", false);
    // _spriteSystem.setScale(buttons[2], 2, 2);

    _positionSystem.create(text);
    _positionSystem.setPosition(text, 850, 400);
    _textSystem.create(text);
    _textSystem.initText(text, "ID: " + std::to_string(_id), 100);

    _lobbyScreenEntities.push_back(parallax[0]);
    _lobbyScreenEntities.push_back(parallax[1]);
    // _lobbyScreenEntities.push_back(buttons[0]);
    _lobbyScreenEntities.push_back(text);

    _created = true;
}

void Engine::JoinScreenSystem::destroySprites(EntityManager &entityManager)
{
    for (int i = 0; i != _lobbyScreenEntities.size(); i++) {
        _spriteSystem.Exist(_lobbyScreenEntities[i]) == true ? _spriteSystem.destroy(_lobbyScreenEntities[i]) : true;
        _textSystem.Exist(_lobbyScreenEntities[i]) == true ? _textSystem.destroy(_lobbyScreenEntities[i]) : true;
        _spriteSystem.Exist(_lobbyScreenEntities[i]) ? _spriteSystem.destroy(_lobbyScreenEntities[i]) : true;
        _velocitySystem.Exist(_lobbyScreenEntities[i]) ? _velocitySystem.destroy(_lobbyScreenEntities[i]) : true;
        _positionSystem.Exist(_lobbyScreenEntities[i]) ? _positionSystem.destroy(_lobbyScreenEntities[i]) : true;
        entityManager.remove(_lobbyScreenEntities[i]);
    }
    //_parallaxSystem.removeParallax();
        _parallaxSystem.removeParallax(_positionSystem, _velocitySystem, entityManager);
        _lobbyScreenEntities.clear();
    _created = false;
}

void Engine::JoinScreenSystem::update(EntityManager &entityManager, SceneManager &sceneManager, NetworkSystem &networkSystem)
{
    _parallaxSystem.update(_positionSystem.getComponent(_lobbyScreenEntities[0]), _velocitySystem.getComponent(_lobbyScreenEntities[0]));
    _parallaxSystem.update(_positionSystem.getComponent(_lobbyScreenEntities[1]), _velocitySystem.getComponent(_lobbyScreenEntities[1]));

    if (_hasFocus()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && _id > 0)
            _id--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            _id++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            joinGame_t package = {JOIN_GAME_PACKAGE, (std::size_t)_id};
            networkSystem.sendPackage(reinterpret_cast<void *>(&package), JOIN_GAME_PACKAGE);
            return;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            sceneManager.setScene(SCENE::MAIN_MENU);
            //destroySprites(entityManager);
            return;
        }
    }

    _textSystem.setText(_lobbyScreenEntities[2], "JOIN ID: " + std::to_string(_id));
}

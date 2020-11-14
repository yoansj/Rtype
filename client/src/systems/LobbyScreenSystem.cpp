/*
** EPITECH PROJECT, 2020
** client
** File description:
** LobbyScreenSytem
*/

#include "LobbyScreenSystem.hpp"

void Engine::LobbyScreenSystem::createSprites(std::array<Entity, 2> parallax, std::array<Entity, 3> buttons, Entity text)
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
    _positionSystem.setPosition(text, 770, 900);
    _textSystem.create(text);
    _textSystem.initText(text, "ID: " + std::to_string(_id), 100);

    _lobbyScreenEntities.push_back(parallax[0]);
    _lobbyScreenEntities.push_back(parallax[1]);
    // _lobbyScreenEntities.push_back(buttons[0]);
    _lobbyScreenEntities.push_back(text);

    _created = true;
}

void Engine::LobbyScreenSystem::destroySprites(EntityManager &entityManager)
{
    if (_created == false) return;
    for (int i = 0; i != _lobbyScreenEntities.size(); i++) {
        _spriteSystem.Exist(_lobbyScreenEntities[i]) == true ? _spriteSystem.destroy(_lobbyScreenEntities[i]) : true;
        _textSystem.Exist(_lobbyScreenEntities[i]) == true ? _textSystem.destroy(_lobbyScreenEntities[i]) : true;
        _velocitySystem.Exist(_lobbyScreenEntities[i]) ? _velocitySystem.destroy(_lobbyScreenEntities[i]) : true;
        _positionSystem.Exist(_lobbyScreenEntities[i]) ? _positionSystem.destroy(_lobbyScreenEntities[i]) : true;
        entityManager.remove(_lobbyScreenEntities[i]);
    }
    _parallaxSystem.removeParallax(_positionSystem, _velocitySystem, entityManager);
    _lobbyScreenEntities.clear();
    _created = false;
}

void Engine::LobbyScreenSystem::update(EntityManager &entityManager, SceneManager &sceneManager)
{
    if (_positionSystem.Exist(_lobbyScreenEntities[0]) && _positionSystem.Exist(_lobbyScreenEntities[1])) {
        _parallaxSystem.update(_positionSystem.getComponent(_lobbyScreenEntities[0]), _velocitySystem.getComponent(_lobbyScreenEntities[0]));
        _parallaxSystem.update(_positionSystem.getComponent(_lobbyScreenEntities[1]), _velocitySystem.getComponent(_lobbyScreenEntities[1]));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        sceneManager.setScene(SCENE::MAIN_MENU);
        destroySprites(entityManager);
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _networkSystem.getPlayerId() == 0) {
        startNewGame_t pkg = {START_NEW_GAME, (std::size_t)_id, "STARTED" };
        _networkSystem.sendPackage(reinterpret_cast<void *>(&pkg), START_NEW_GAME);
        return;
    }
    if (_textSystem.Exist(_lobbyScreenEntities[2]))
        _textSystem.setText(_lobbyScreenEntities[2], "Lobby Id: " + std::to_string(_id));
}

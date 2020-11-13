/*
** EPITECH PROJECT, 2020
** client
** File description:
** MenuScreenSystem
*/

#include "MenuScreenSystem.hpp"

void Engine::MenuScreenSystem::createSprites(std::array<Entity, 2> parallax, std::array<Entity, 3> buttons)
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

    _spriteSystem.create(buttons[0]);
    _positionSystem.create(buttons[0]);
    _positionSystem.setPosition(buttons[0], 700, 200);
    _spriteSystem.initSprite(buttons[0], "../client/assets/create.png", false);
    _spriteSystem.setScale(buttons[0], 2, 2);

    _spriteSystem.create(buttons[1]);
    _positionSystem.create(buttons[1]);
    _positionSystem.setPosition(buttons[1], 700, 400);
    _spriteSystem.initSprite(buttons[1], "../client/assets/join.png", false);
    _spriteSystem.setScale(buttons[1], 2, 2);

    _spriteSystem.create(buttons[2]);
    _positionSystem.create(buttons[2]);
    _positionSystem.setPosition(buttons[2], 700, 600);
    _spriteSystem.initSprite(buttons[2], "../client/assets/quit.png", false);
    _spriteSystem.setScale(buttons[2], 2, 2);

    _menuScreenEntities.push_back(parallax[0]);
    _menuScreenEntities.push_back(parallax[1]);
    _menuScreenEntities.push_back(buttons[0]);
    _menuScreenEntities.push_back(buttons[1]);
    _menuScreenEntities.push_back(buttons[2]);

    _created = true;
}

void Engine::MenuScreenSystem::destroySprites(EntityManager &entityManager)
{
    for (int i = 0; i != _menuScreenEntities.size(); i++) {
        _spriteSystem.Exist(_menuScreenEntities[i]) ? _spriteSystem.destroy(_menuScreenEntities[i]) : false;
        _velocitySystem.Exist(_menuScreenEntities[i]) ? _velocitySystem.destroy(_menuScreenEntities[i]) : false;
        _positionSystem.Exist(_menuScreenEntities[i]) ? _positionSystem.destroy(_menuScreenEntities[i]) : false;
        entityManager.remove(_menuScreenEntities[i]);
    }
    _parallaxSystem.removeParallax(_positionSystem, _velocitySystem, entityManager);
    _menuScreenEntities.clear();
    _created = false;
}

void Engine::MenuScreenSystem::update(EntityManager &entityManager, SceneManager &sceneManager, NetworkSystem &networkSystem)
{
    _parallaxSystem.update(_positionSystem.getComponent(_menuScreenEntities[0]), _velocitySystem.getComponent(_menuScreenEntities[0]));
    _parallaxSystem.update(_positionSystem.getComponent(_menuScreenEntities[1]), _velocitySystem.getComponent(_menuScreenEntities[1]));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            if (_choice == choice::CREATE) {
                createNewGame_t package = {CREATE_NEW_GAME, "NewGame"};
                destroySprites(entityManager);
                sceneManager.setScene(SCENE::LOBBY);
                networkSystem.sendPackage(static_cast<void *>(&package), CREATE_NEW_GAME);
                return;
            }
            else if (_choice == choice::JOIN)
                sceneManager.setScene(SCENE::JOIN_GAME);
            else if (_choice == choice::QUIT)
                sceneManager.setScene(SCENE::GAME_END);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _isPressed == false) {
        _choice == 2 ? _choice = 0 : _choice++;
        _isPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _isPressed == false) {
        _choice == 0 ? _choice = 2 : _choice--;
        _isPressed = true;
    }
    _choice == choice::CREATE ? _spriteSystem.changeTexture(_menuScreenEntities[2], "../client/assets/createPressed.png") : _spriteSystem.changeTexture(_menuScreenEntities[2], "../client/assets/create.png");
    _choice == choice::JOIN ? _spriteSystem.changeTexture(_menuScreenEntities[3], "../client/assets/joinPressed.png") : _spriteSystem.changeTexture(_menuScreenEntities[3], "../client/assets/join.png");
    _choice == choice::QUIT ? _spriteSystem.changeTexture(_menuScreenEntities[4], "../client/assets/quitPressed.png") : _spriteSystem.changeTexture(_menuScreenEntities[4], "../client/assets/quit.png");
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _isPressed = false;
}


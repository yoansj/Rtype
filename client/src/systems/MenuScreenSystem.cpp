/*
** EPITECH PROJECT, 2020
** client
** File description:
** MenuScreenSystem
*/

#include "MenuScreenSystem.hpp"

void Engine::MenuScreenSystem::createSprites(Entity parallax, std::array<Entity, 3> buttons)
{
    _spriteSystem.create(parallax);
    _positionSystem.create(parallax);
    _positionSystem.setPosition(parallax, -1800, 0);
    _spriteSystem.initSprite(parallax, "../client/assets/background.png", false);
    _velocitySystem.create(parallax);
    _velocitySystem.setVelocity(parallax, 1, 1);
    _parallaxSystem.setBackgroundEntity(parallax);

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

    _menuScreenEntities.push_back(parallax);
    _menuScreenEntities.push_back(buttons[0]);
    _menuScreenEntities.push_back(buttons[1]);
    _menuScreenEntities.push_back(buttons[2]);

    _created = true;
}

void Engine::MenuScreenSystem::destroySprites(EntityManager &entityManager)
{
    for (int i = 0; i != _menuScreenEntities.size(); i++) {
        _spriteSystem.destroy(_menuScreenEntities[i]);
        _velocitySystem.destroy(_menuScreenEntities[i]);
        _positionSystem.destroy(_menuScreenEntities[i]);
        _parallaxSystem.destroy(_menuScreenEntities[i]);
        entityManager.remove(_menuScreenEntities[i]);
    }
    _created = false;
}

void Engine::MenuScreenSystem::update(EntityManager &entityManager, SceneManager &sceneManager)
{
    _parallaxSystem.update(_positionSystem.getComponent(_menuScreenEntities[0]), _velocitySystem.getComponent(_menuScreenEntities[0]));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            if (_choice == choice::CREATE)
                std::cout << "create\n";
            if (_choice == choice::JOIN)
                std::cout << "join\n";
            std::cout << _choice << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _isPressed == false) {
        _choice == 2 ? _choice = 0 : _choice++;
        _isPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _isPressed == false) {
        _choice == 0 ? _choice = 2 : _choice--;
        _isPressed = true;
    }
    _choice == choice::CREATE ? _spriteSystem.changeTexture(_menuScreenEntities[1], "../client/assets/createPressed.png") : _spriteSystem.changeTexture(_menuScreenEntities[1], "../client/assets/create.png");
    _choice == choice::JOIN ? _spriteSystem.changeTexture(_menuScreenEntities[2], "../client/assets/joinPressed.png") : _spriteSystem.changeTexture(_menuScreenEntities[2], "../client/assets/join.png");
    _choice == choice::QUIT ? _spriteSystem.changeTexture(_menuScreenEntities[3], "../client/assets/quitPressed.png") : _spriteSystem.changeTexture(_menuScreenEntities[3], "../client/assets/quit.png");
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _isPressed = false;
}


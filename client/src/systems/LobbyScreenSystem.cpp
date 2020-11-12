/*
** EPITECH PROJECT, 2020
** client
** File description:
** LobbyScreenSytem
*/

#include "LobbyScreenSystem.hpp"

void Engine::LobbyScreenSystem::createSprites(Entity parallax, std::array<Entity, 3> buttons, Entity text)
{
    _spriteSystem.create(parallax);
    _positionSystem.create(parallax);
    _positionSystem.setPosition(parallax, -1800, 0);
    _spriteSystem.initSprite(parallax, "../client/assets/background.png", false);
    _velocitySystem.create(parallax);
    _velocitySystem.setVelocity(parallax, 5, 5);
    _parallaxSystem.setBackgroundEntity(parallax);

    // _spriteSystem.create(buttons[0]);
    // _positionSystem.create(buttons[0]);
    // _positionSystem.setPosition(buttons[0], 700, 200);
    // _spriteSystem.initSprite(buttons[0], "../client/assets/create.png", false);
    // _spriteSystem.setScale(buttons[0], 2, 2);

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

    _lobbyScreenEntities.push_back(parallax);
    _lobbyScreenEntities.push_back(text);
    // _lobbyScreenEntities.push_back(buttons[0]);
    // _lobbyScreenEntities.push_back(buttons[1]);
    // _lobbyScreenEntities.push_back(buttons[2]);

    _created = true;
}

void Engine::LobbyScreenSystem::destroySprites(EntityManager &entityManager)
{
    for (int i = 0; i != _lobbyScreenEntities.size(); i++) {
        _spriteSystem.destroy(_lobbyScreenEntities[i]);
        _velocitySystem.destroy(_lobbyScreenEntities[i]);
        _positionSystem.destroy(_lobbyScreenEntities[i]);
        _parallaxSystem.destroy(_lobbyScreenEntities[i]);
        entityManager.remove(_lobbyScreenEntities[i]);
    }
    _created = false;
}

void Engine::LobbyScreenSystem::update(EntityManager &entityManager, SceneManager &sceneManager)
{
    _parallaxSystem.update(_positionSystem.getComponent(_lobbyScreenEntities[0]), _velocitySystem.getComponent(_lobbyScreenEntities[0]));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && _id > 1)
        _id--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _id++;

    _textSystem.setText(_lobbyScreenEntities[1], "ID: " + std::to_string(_id));
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    //         if (_choice == choice::CREATE)
    //             sceneManager.setScene(SCENE::GAME);
    //         else if (_choice == choice::JOIN)
    //             sceneManager.setScene(SCENE::JOIN_GAME);
    //         else if (_choice == choice::QUIT)
    //             sceneManager.setScene(SCENE::GAME_END);
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _isPressed == false) {
    //     _choice == 2 ? _choice = 0 : _choice++;
    //     _isPressed = true;
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _isPressed == false) {
    //     _choice == 0 ? _choice = 2 : _choice--;
    //     _isPressed = true;
    // }
    // _choice == choice::CREATE ? _spriteSystem.changeTexture(_lobbyScreenEntities[1], "../client/assets/createPressed.png") : _spriteSystem.changeTexture(_lobbyScreenEntities[1], "../client/assets/create.png");
    // _choice == choice::JOIN ? _spriteSystem.changeTexture(_lobbyScreenEntities[2], "../client/assets/joinPressed.png") : _spriteSystem.changeTexture(_lobbyScreenEntities[2], "../client/assets/join.png");
    // _choice == choice::QUIT ? _spriteSystem.changeTexture(_lobbyScreenEntities[3], "../client/assets/quitPressed.png") : _spriteSystem.changeTexture(_lobbyScreenEntities[3], "../client/assets/quit.png");
    // if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    //     _isPressed = false;
}

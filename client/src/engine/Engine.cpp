/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Engine
*/

#include "Engine.hpp"
#include <fstream>

Engine::Engine::Engine() :
    _window(std::make_shared<sf::RenderWindow>(sf::VideoMode(1800, 1000), "R-Type")),
    _renderer(_window), _tcpClient("localhost", 7172)
{
}

Engine::Engine::~Engine()
{
}

/**
 * @brief  This function runs the engine
 * @returns None
 */
void Engine::Engine::run()
{
    sf::Clock clock;
    createNewGame_t package = {CREATE_NEW_GAME, "NewGamee e"};

    while (_window->isOpen()) {
        _window->clear(sf::Color::Blue);
        _tcpClient.receivePackage();
        while (_window->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                _window->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                _tcpClient.sendPackage(static_cast<void *>(&package));
                std::cout << "ziak les paquets partent" << std::endl;
            }
        }
        if (clock.getElapsedTime().asMilliseconds() >= 1000.0 / 60.0) {
            updateSystems();
            _renderer.doRender(_systems);
            _window->display();
            clock.restart();
        }
    }
}

/**
 * @brief  This function is used to update all systems
 * @retval None
 */
void Engine::Engine::updateSystems()
{
    if (_sceneManager.getScene() == SCENE::TITLE_SCREEN) {
        if (!_systems.titleScreen.isCreated()) {
            _systems.titleScreen.createSprites(_entityManager.create(), _entityManager.create());
        }
        _systems.titleScreen.update(_entityManager, _sceneManager);
    }
    if (_sceneManager.getScene() == SCENE::GAME) {
        if (!_systems.gameScreen.isCreated()) {
            _systems.gameScreen.createSprites(_entityManager.create());
        }
        _systems.gameScreen.update(_entityManager, _sceneManager);
    }
    if (_sceneManager.getScene() == SCENE::MAIN_MENU) {
        if (!_systems.menuScreen.isCreated()) {
            _systems.menuScreen.createSprites(_entityManager.create(), {_entityManager.create(), _entityManager.create(), _entityManager.create()});
        }
        _systems.menuScreen.update(_entityManager, _sceneManager);
    }
    if (_sceneManager.getScene() == SCENE::LOBBY) {
        if (!_systems.lobbyScreen.isCreated()) {
            _systems.lobbyScreen.createSprites(_entityManager.create(), {_entityManager.create(), _entityManager.create(), _entityManager.create()}, _entityManager.create());
        }
        _systems.lobbyScreen.update(_entityManager, _sceneManager);
    }
    if (_sceneManager.getScene() == SCENE::GAME_END)
            _window->close();


    /*auto player = _systems.playerSystem.getPlayer();
    auto bgEntity = _systems.parallaxSystem.getBackgroundEntity();
    _systems.positionSystem.update();
    _systems.spriteSystem.update();
    _systems.parallaxSystem.update(_systems.positionSystem.getComponent(bgEntity), _systems.velocitySystem.getComponent(bgEntity));
    _systems.inputSystem.update(_systems.positionSystem.getComponent(player), _systems.velocitySystem.getComponent(player), _systems.spriteSystem.getComponent(player));*/
}
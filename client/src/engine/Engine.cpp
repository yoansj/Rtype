/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Engine
*/

#include "Engine.hpp"
#include <fstream>

Engine::Engine::Engine() :
    _window(std::make_shared<sf::RenderWindow>(sf::VideoMode(1800, 1000), "R-Type")), _renderer(_window)
{
}

Engine::Engine::~Engine()
{
}

void Engine::Engine::initGame()
{
    auto player = _entityManager.create();
    _systems.spriteSystem.create(player);
    _systems.positionSystem.create(player);
    _systems.positionSystem.setPosition(player, 500, 500);
    _systems.spriteSystem.initSprite(player,"../client/assets/sprite.png");
    _systems.playerSystem.setPlayer(player);
    _systems.velocitySystem.create(player);
    _systems.velocitySystem.setVelocity(player, 1, 1);
    std::cout << "Size: " << _systems.spriteSystem.getComponent(player).texture.getSize().x << std::endl;

    auto another = _entityManager.create();
    _systems.spriteSystem.create(another);
    _systems.positionSystem.create(another);
    _systems.positionSystem.setPosition(another, 100, 100);
    _systems.spriteSystem.initSprite(another, "../client/assets/r-typesheet44.gif");
    std::cout << "Size: " << _systems.spriteSystem.getComponent(another).texture.getSize().x << std::endl;

    // auto bg = _entityManager.create();
    // _systems.spriteSystem.create(bg);
    // _systems.positionSystem.create(bg);
    // _systems.positionSystem.setPosition(bg, 0, 0);
    // _systems.spriteSystem.initSprite(bg, "../client/assets/background.png");
    // // _systems.playerSystem.setPlayer(bg);
    // _systems.velocitySystem.setVelocity(bg, 1, 1);



    auto bg = _entityManager.create();
    _systems.spriteSystem.create(bg);
    _systems.positionSystem.create(bg);
    _systems.positionSystem.setPosition(bg, -1800, 0);
    _systems.playerSystem.setPlayer(bg);
    _systems.spriteSystem.initSprite(bg, "../client/assets/background.png");
    _systems.velocitySystem.create(bg);
    _systems.velocitySystem.setVelocity(bg, 1, 1);
    _systems.parallaxSystem.setBackgroundEntity(bg);


    _systems.monsterLoaderSystem.load({std::string(ROOT_PATH) + "build/lib/libfrog.so"});
    monsterGenerator frogFactory = reinterpret_cast<monsterGenerator>(_systems.monsterLoaderSystem.getFactory(0));
    auto frog = frogFactory(_entityManager, _systems);


    // Network
    _systems.networkSystem.setPort(7171);
    _systems.networkSystem.setRecipient("localhost");
    connectionToServer_t package = {0, "Connection"};
    _systems.networkSystem.send(static_cast<void *>(&package));
}

/**
 * @brief  This function runs the engine
 * @returns None
 */
void Engine::Engine::run()
{
    initGame();
    while (_window->isOpen()) {
        _window->clear(sf::Color::Blue);
        while (_window->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                _window->close();
        }
        updateSystems();
        _renderer.doRender(_systems);
        _window->display();
    }
}

/**
 * @brief  This function is used to update all systems
 * @retval None
 */
void Engine::Engine::updateSystems()
{
    auto player = _systems.playerSystem.getPlayer();
    _systems.positionSystem.update();
    _systems.spriteSystem.update();
    _systems.parallaxSystem.update(_systems.positionSystem.getComponent(player), _systems.velocitySystem.getComponent(player));
    // _systems.inputSystem.update(_systems.positionSystem.getComponent(player), _systems.velocitySystem.getComponent(player));
}
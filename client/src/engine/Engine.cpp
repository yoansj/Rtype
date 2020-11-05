/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine::Engine() :
    _window(std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 1000), "R-Type")), _renderer(_window)
{
    auto test = _entityManager.create();
    _systems.spriteSystem.create(test);
    _systems.positionSystem.create(test);
    _systems.positionSystem.setPosition(test, 500, 500);
    _systems.spriteSystem.setWindow(_window);
    _systems.spriteSystem.initSprite(test, "../client/assets/sprite.png");
    _systems.playerSystem.setPlayer(test);
    _systems.velocitySystem.create(test);
    _systems.velocitySystem.setVelocity(test, 1, 1);
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
    _systems.inputSystem.update(_systems.positionSystem.getComponent(player), _systems.velocitySystem.getComponent(player));
}
/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine::Engine() :
    _window(std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 1000), "R-Type")),
    _systems(Systems::Get())
{
    auto test = _entityManager.create();
    _systems.Get().spriteSystem.create(test);
    _systems.Get().positionSystem.create(test);
    _systems.Get().positionSystem.setPosition(test, 500, 500);
    _systems.Get().spriteSystem.initSprite(test, "sprite.png");
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
        _window->clear(sf::Color::Magenta);
        while (_window->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                _window->close();
        }
        updateSystems();
        _window->display();
    }
}

/**
 * @brief  This function is used to update all systems
 * @retval None
 */
void Engine::Engine::updateSystems()
{
    _systems.positionSystem.update();
    _systems.spriteSystem.update();
}
/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine::Engine() :
    _window(sf::VideoMode(1000, 1000), "R-Type")
{
}

Engine::Engine::~Engine()
{
}

void Engine::Engine::update()
{
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                _window.close();
        }
    }
}
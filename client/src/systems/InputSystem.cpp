/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** InputSystem
*/

#include "InputSystem.hpp"

void Engine::InputSystem::update(Position &pos, Velocity &vel) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pos.x -= vel.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pos.x += vel.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pos.y -= vel.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pos.y += vel.y;
    }
}
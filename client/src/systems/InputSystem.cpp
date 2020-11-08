/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** InputSystem
*/

#include "InputSystem.hpp"

void Engine::InputSystem::update(Position &pos, Velocity &vel, Sprite &spr) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pos.x -= vel.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pos.x += vel.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pos.y -= vel.y;
        spr.rect.left = 320;
        spr.rect.width = 152;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pos.y += vel.y;
        spr.rect.left = 0;
        spr.rect.width = 160;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        spr.rect.left = 170;
        spr.rect.width = 148;
    }
}
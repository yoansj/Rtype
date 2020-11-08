/*
** EPITECH PROJECT, 2020
** client
** File description:
** ParallaxSystem
*/

#include "ParallaxSystem.hpp"

void Engine::ParallaxSystem::update(Position &pos, Velocity &vel)
{
    _time = _clock.getElapsedTime();
    if (pos.x <= -1800)
        pos.x = 0;
    if (_time.asMicroseconds() >= 2000) {
        _clock.restart();
        pos.x -= vel.x;
    }
}
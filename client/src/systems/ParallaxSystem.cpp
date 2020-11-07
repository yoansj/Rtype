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
    if (pos.x >= 0)
        pos.x = -1800;
    if (_time.asMicroseconds() >= 1500) {
        _clock.restart();
        pos.x += vel.x;
    }
    // if (t == 1000) {
    //     t = 0;  
    //     pos.x += vel.x;
    // }
    // else
    //     t += 1;
    // if (pos.x == 2000)
    //     pos.x = 0;
}
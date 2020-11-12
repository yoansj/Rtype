/*
** EPITECH PROJECT, 2020
** client
** File description:
** ParallaxSystem
*/

#include "ParallaxSystem.hpp"

void Engine::ParallaxSystem::update(Position &pos, Velocity &vel)
{
    if (pos.x <= -1800)
        pos.x = 0;
    pos.x -= vel.x;
}
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

void Engine::ParallaxSystem::removeParallax(PositionSystem &positionSystem, VelocitySystem &velocitySytem, EntityManager &entityManager)
{
    if (positionSystem.Exist(_background))
        positionSystem.destroy(_background);
    if (velocitySytem.Exist(_background))
        velocitySytem.destroy(_background);
    entityManager.remove(_background);
}

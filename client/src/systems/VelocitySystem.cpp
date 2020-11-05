/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** VelocitySystem
*/

#include "VelocitySystem.hpp"


/**
 * @brief  Gets position of entity
 * @param  e: The entity that you want to get the position
 * @returns A position component
 */
Engine::Velocity &Engine::VelocitySystem::getVelocity(Entity e) {
    return (
        _components.getComponent(e)
    );
}

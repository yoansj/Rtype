/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** PositionSystem
*/

#include "PositionSystem.hpp"

/**
 * @brief  Gets position of entity
 * @param  e: The entity that you want to get the position
 * @returns A position component
 */
Engine::Position &Engine::PositionSystem::getPosition(Entity e) {
    return (
        _components.getComponent(e)
    );
}

/**
 * @brief  Updates the position of the entity
 * @param  e: The entity to update
 * @param  x: The new x pos
 * @param  y: The new y pos
 * @returns A boolean to know if the value changed
 */
bool Engine::PositionSystem::setPosition(Entity e, float x, float y) {
    auto &pos = _components.getComponent(e);

    pos.x = x;
    pos.y = y;
    return (true);
}
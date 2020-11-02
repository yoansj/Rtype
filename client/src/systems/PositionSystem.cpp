/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** PositionSystem
*/

#include "PositionSystem.hpp"

Position &PositionSystem::getPosition(Entity e) {
    return (
        _components.getComponent(e)
    );
}

bool PositionSystem::setPosition(Entity e, float x, float y) {
    auto pos = _components.getComponent(e);

    pos.x = x;
    pos.y = y;
    return (true);
}
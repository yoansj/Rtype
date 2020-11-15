/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include "Component.hpp"

namespace Engine {

    struct Position : public Component {
        Position(Entity e) : Component(e) {entity = e;};
        Position() = default;
        float x;
        float y;
    };

}

#endif /* !POSITION_HPP_ */

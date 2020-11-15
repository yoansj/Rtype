/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Hitbox
*/

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include "Component.hpp"

namespace Engine {

    enum HitboxType {
        BULLET,
        MONSTER,
        PLAYER,
    };

    struct Hitbox : public Component {
        Hitbox(Entity e) : Component(e) {entity = e;};
        Hitbox() = default;
        float width;
        float height;
        HitboxType type;
    };

}

#endif /* !HITBOX_HPP_ */

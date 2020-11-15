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

    /**
     * @brief Enum to know the type of hitbox for an entity.
     * 
     */
    enum HitboxType {
        BULLET,
        MONSTER,
        PLAYER,
    };

    /**
     * @brief Hitbox component.
     * 
     */
    struct Hitbox : public Component {
        /**
         * @brief Construct a new Hitbox object
         * 
         * @param params1 Entity e 
         */
        Hitbox(Entity e) : Component(e) {entity = e;};

        /**
         * @brief Construct a new Hitbox object
         * 
         */
        Hitbox() = default;
        float width;
        float height;
        HitboxType type;
    };

}

#endif /* !HITBOX_HPP_ */

/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** HitboxSystem
*/

#ifndef HITBOXSYSTEM_HPP_
#define HITBOXSYSTEM_HPP_

#include "System.hpp"
#include "Hitbox.hpp"

namespace Engine {

    /**
     * @brief  System used for collisions
     */
    class HitboxSystem : public System<Hitbox> {
        public:
            HitboxSystem() : System() {};
            ~HitboxSystem() = default;

            void update() override {};

            void setHitbox(Entity e, float w, float h, HitboxType type) {
                auto &hb = _components.getComponent(e);

                hb.width = w;
                hb.height = h;
                hb.type = type;
            }

            bool collides(Entity a, Position aPos, Entity b, Position bPos) {
                return (true);
            }
    };

}

#endif /* !HITBOXSYSTEM_HPP_ */

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
            /**
             * @brief Construct a new Hitbox System object
             * 
             */
            HitboxSystem() : System() {};

            /**
             * @brief Destroy the Hitbox System object
             * 
             */
            ~HitboxSystem() = default;

            void update() override {};

            /**
             * @brief Set the Hitbox object
             * 
             * @param Entity e 
             * @param float w 
             * @param float h 
             * @param HitboxType type 
             */
            void setHitbox(Entity e, float w, float h, HitboxType type) {
                auto &hb = _components.getComponent(e);

                hb.width = w;
                hb.height = h;
                hb.type = type;
            }

            /**
             * @brief Checks if the entity collides with another entity.
             * 
             * @param params1 Entity a 
             * @param params2 Position aPos 
             * @param params3 Entity b 
             * @param params4 Position bPos 
             * @return value bool 
             */
            bool collides(Entity a, Position aPos, Entity b, Position bPos) {
                auto &aHitbox = _components.getComponent(a);
                auto &bHitbox = _components.getComponent(b);

                if (aPos.x < bPos.x + bHitbox.width &&
                    aPos.x + aHitbox.width > bPos.x &&
                    aPos.y < bPos.y + bHitbox.height &&
                    aHitbox.height + aPos.y > bPos.y) {
                    return (true);
                }
                return (false);

                if (aPos.x < bPos.x + bHitbox.width &&
                aPos.x + aHitbox.width > bPos.x &&
                aPos.y < bPos.y + bHitbox.height &&
                aHitbox.height + aPos.y > bPos.y)
                    return (true);
                return (false);
            }
    };

}

#endif /* !HITBOXSYSTEM_HPP_ */

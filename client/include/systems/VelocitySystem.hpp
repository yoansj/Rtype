/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** VelocitySystem
*/

#ifndef VELOCITYSYSTEM_HPP_
#define VELOCITYSYSTEM_HPP_

#include "System.hpp"
#include "Velocity.hpp"
#include "Entity.hpp"

namespace Engine {

    /**
     * @brief  Position system used on the Position component
     */
    class VelocitySystem : public System<Velocity> {
        public:
            VelocitySystem() : System() {};
            ~VelocitySystem() = default;

            void update() override {};

            bool setVelocity(Entity e, float x, float y) {
                auto &pos = _components.getComponent(e);
                pos.x = x;
                pos.y = y;
                return (true);};
            Velocity &getVelocity(Entity e);
    };

}

#endif /* !VELOCITYSYSTEM_HPP_ */

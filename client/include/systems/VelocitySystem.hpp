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
     * @brief  Velocity system used on the Velocity component
     */
    class VelocitySystem : public System<Velocity> {
        public:
            VelocitySystem() : System() {};
            ~VelocitySystem() = default;

            /**
             * @brief Update the system.
             * 
             */
            void update() override {};

            /**
             * @brief Set the Velocity to a Entity
             * 
             * @param Entity e 
             * @param float x 
             * @param float y 
             * @return bool 
             */
            bool setVelocity(Entity e, float x, float y) {
                auto &pos = _components.getComponent(e);
                pos.x = x;
                pos.y = y;
                return (true);};

            /**
             * @brief Get the Velocity of a Entity
             * 
             * @param e 
             * @return Velocity& 
             */
            Velocity &getVelocity(Entity e);
    };

}

#endif /* !VELOCITYSYSTEM_HPP_ */

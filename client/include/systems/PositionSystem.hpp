/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
#define POSITIONSYSTEM_HPP_

#include "System.hpp"
#include "Position.hpp"
#include "Entity.hpp"

namespace Engine {

    /**
     * @brief  Position system used on the Position component
     */
    class PositionSystem : public System<Position> {
        public:
            PositionSystem() : System() {};
            ~PositionSystem() = default;

            void update() override {};

            bool setPosition(Entity e, float x, float y);
            Position &getPosition(Entity e);
    };

}

#endif /* !POSITIONSYSTEM_HPP_ */

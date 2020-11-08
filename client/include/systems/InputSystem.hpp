/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** InputSystem
*/

#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_

#include "System.hpp"
#include "Position.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Velocity.hpp"
#include "Sprite.hpp"

namespace Engine {

    /**
     * @brief  Position system used on the Position component
     */
    class InputSystem : public System<Position> {
        public:
            InputSystem() : System() {};
            ~InputSystem() = default;

            void update(Position &pos, Velocity &vel, Sprite &spr);
    };

}


#endif /* !INPUTSYSTEM_HPP_ */

/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Systems
*/

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "PositionSystem.hpp"
#include "SpriteSystem.hpp"
#include "PlayerSystem.hpp"
#include "InputSystem.hpp"
#include "VelocitySystem.hpp"

namespace Engine {
    class SystemManager {
        public:
            SystemManager() = default;
            ~SystemManager() = default;

            PositionSystem positionSystem;
            SpriteSystem spriteSystem;
            PlayerSystem playerSystem;
            InputSystem inputSystem;
            VelocitySystem velocitySystem;

        private:

    };
}

#endif /* !SYSTEM_H_ */

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

namespace Engine {
    class SystemManager {
        public:
            SystemManager() = default;
            ~SystemManager() = default;

            PositionSystem positionSystem;
            SpriteSystem spriteSystem;

        private:

    };
}

#endif /* !SYSTEM_H_ */

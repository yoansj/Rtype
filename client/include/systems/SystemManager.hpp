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
#include "MonsterLoaderSystem.hpp"
#include "ParallaxSystem.hpp"
#include "NetworkSystem.hpp"
#include "TitleScreenSystem.hpp"

namespace Engine {
    class SystemManager {
        public:
            SystemManager() : titleScreen(spriteSystem, velocitySystem, positionSystem) {};
            ~SystemManager() = default;

            PositionSystem positionSystem;
            SpriteSystem spriteSystem;
            PlayerSystem playerSystem;
            InputSystem inputSystem;
            VelocitySystem velocitySystem;
            MonsterLoaderSystem monsterLoaderSystem;
            ParallaxSystem parallaxSystem;
            NetworkSystem networkSystem;
            TitleScreenSystem titleScreen;

        private:

    };
}

#endif /* !SYSTEM_H_ */

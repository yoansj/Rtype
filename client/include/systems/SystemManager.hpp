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
#include "InputSystem.hpp"
#include "VelocitySystem.hpp"
#include "MonsterLoaderSystem.hpp"
#include "ParallaxSystem.hpp"
#include "TextSystem.hpp"
#include "NetworkSystem.hpp"
#include "TitleScreenSystem.hpp"
#include "GameScreenSystem.hpp"
#include "MenuScreenSystem.hpp"
#include "LobbyScreenSystem.hpp"
#include "JoinScreenSystem.hpp"

namespace Engine {
    class SystemManager {
        public:
            SystemManager() : titleScreen(spriteSystem, velocitySystem, positionSystem),
            gameScreen(spriteSystem, velocitySystem, positionSystem, parallaxSystem),
            menuScreen(spriteSystem, velocitySystem, positionSystem, parallaxSystem),
            lobbyScreen(spriteSystem, velocitySystem,positionSystem, parallaxSystem, textSystem, networkSystem),
            joinScreen(spriteSystem, velocitySystem,positionSystem, parallaxSystem, textSystem) {};
            ~SystemManager() = default;

            PositionSystem positionSystem;
            SpriteSystem spriteSystem;
            InputSystem inputSystem;
            VelocitySystem velocitySystem;
            MonsterLoaderSystem monsterLoaderSystem;
            ParallaxSystem parallaxSystem;
            TextSystem textSystem;

            NetworkSystem networkSystem;
            TitleScreenSystem titleScreen;
            GameScreenSystem gameScreen;
            MenuScreenSystem menuScreen;
            LobbyScreenSystem lobbyScreen;
            JoinScreenSystem joinScreen;

        private:

    };
}

#endif /* !SYSTEM_H_ */

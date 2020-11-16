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
#include "HitboxSystem.hpp"
#include "StatusSystem.hpp"
#include "SoundSystem.hpp"

namespace Engine {

    /**
     * @brief Manager for all the systems
     * 
     */
    class SystemManager {
        public:
            SystemManager(std::string const &ip) : titleScreen(spriteSystem, velocitySystem, positionSystem),
            gameScreen(spriteSystem, velocitySystem, positionSystem, parallaxSystem, soundSystem),
            menuScreen(spriteSystem, velocitySystem, positionSystem, parallaxSystem, soundSystem),
            lobbyScreen(spriteSystem, velocitySystem,positionSystem, parallaxSystem, textSystem, networkSystem),
            joinScreen(spriteSystem, velocitySystem,positionSystem, parallaxSystem, textSystem), networkSystem(ip) {};
            ~SystemManager() = default;

            PositionSystem positionSystem;
            SpriteSystem spriteSystem;
            InputSystem inputSystem;
            VelocitySystem velocitySystem;
            MonsterLoaderSystem monsterLoaderSystem;
            ParallaxSystem parallaxSystem;
            TextSystem textSystem;
            HitboxSystem hitboxSystem;
            StatusSystem statusSystem;
            SoundSystem soundSystem;

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

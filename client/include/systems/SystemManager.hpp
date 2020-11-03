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
            static SystemManager &Get() {static SystemManager sys; return(sys);};

            PositionSystem positionSystem;
            Engine::SpriteSystem spriteSystem;

        private:
            SystemManager &operator= (const SystemManager&) = delete;
            SystemManager (const SystemManager&) = delete;
            SystemManager() = default;
            ~SystemManager() = default;
    };
}

#endif /* !SYSTEM_H_ */

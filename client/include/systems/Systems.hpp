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
    class Systems {
        public:
            static Systems &Get() {static Systems sys; return(sys);};

            PositionSystem positionSystem;
            SpriteSystem spriteSystem;

        private:
            Systems &operator= (const Systems&) = delete;
            Systems (const Systems&) = delete;
            Systems() = default;
            ~Systems() = default;
    };
}

#endif /* !SYSTEM_H_ */

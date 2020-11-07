/*
** EPITECH PROJECT, 2020
** client
** File description:
** ParallaxSystem
*/

#ifndef PARALLAXSYSTEM_HPP_
#define PARALLAXSYSTEM_HPP_

#include "System.hpp"
#include "Sprite.hpp"
#include "Position.hpp"
#include "Velocity.hpp"

namespace Engine {
    class ParallaxSystem: public System<Position> {
        public:
            ParallaxSystem() : System() {};
            ~ParallaxSystem() = default;

            void update(Position &pos, Velocity &vel);

        protected:
        private:
            sf::Clock _clock;
            sf::Time _time;
    };
}

#endif /* !PARALLAXSYSTEM_HPP_ */

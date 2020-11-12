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
#include "PositionSystem.hpp"
#include "VelocitySystem.hpp"

namespace Engine {
    class ParallaxSystem {
        public:
            ParallaxSystem() {};
            ~ParallaxSystem() = default;

            void update(Position &pos, Velocity &vel);

            void setBackgroundEntity(Entity background) {_background = background;};

            Entity getBackgroundEntity() const {return (_background);};

            void removeParallax(PositionSystem &positionSystem, VelocitySystem &velocitySytem, EntityManager &entityManager);

        private:
            sf::Clock _clock;
            sf::Time _time;
            Entity _background;
    };
}

#endif /* !PARALLAXSYSTEM_HPP_ */

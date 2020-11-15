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

    /**
     * @brief Parallax System for the menu and the game.
     * 
     */
    class ParallaxSystem {
        public:
            ParallaxSystem() {};
            ~ParallaxSystem() = default;

            /**
             * @brief Update the Position and the Velocity
             * 
             * @param Position &pos 
             * @param Velocity &vel 
             */
            void update(Position &pos, Velocity &vel);

            /**
             * @brief Set the Background Entity
             * 
             * @param Entity background 
             */
            void setBackgroundEntity(Entity background) {_background = background;};

            /**
             * @brief Get the Background Entity
             * 
             * @return Entity 
             */
            Entity getBackgroundEntity() const {return (_background);};

            /**
             * @brief Remove the parallax active
             * 
             * @param PositionSystem &positionSystem 
             * @param VelocitySystem &velocitySytem 
             * @param EntityManager &entityManager 
             */
            void removeParallax(PositionSystem &positionSystem, VelocitySystem &velocitySytem, EntityManager &entityManager);

        private:
            sf::Clock _clock;
            sf::Time _time;
            Entity _background;
    };
}

#endif /* !PARALLAXSYSTEM_HPP_ */

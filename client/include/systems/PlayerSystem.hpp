/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** PlayerSystem
*/

#ifndef PLAYERSYSTEM_HPP_
#define PLAYERSYSTEM_HPP_

#include "System.hpp"
#include "Position.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

namespace Engine {

    /**
     * @brief  Position system used on the Position component
     */
    class PlayerSystem : public System<Player> {
        public:
            PlayerSystem() : System() {};
            ~PlayerSystem() = default;

            void update() override {};

            // void setPlayer();
            void setPlayer(Entity e);
            Entity getPlayer() const { return (_player);};

            void movePlayer(sf::Keyboard input);
        private:
            Entity _player;
    };

}

#endif /* !PLAYERSYSTEM_HPP_ */

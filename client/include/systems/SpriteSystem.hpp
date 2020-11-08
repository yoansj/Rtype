/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SpriteSystem
*/

#ifndef SPRITESYSTEM_HPP_
#define SPRITESYSTEM_HPP_

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

#include "System.hpp"
#include "Sprite.hpp"
#include "EngineError.hpp"

namespace Engine {

    /**
     * @brief  Sprite system used on the Sprite component
     */
    class SpriteSystem : public System<Sprite> {
        public:
            SpriteSystem();
            ~SpriteSystem() = default;

            void update();

            bool initSprite(Entity e, std::string const &filepath);

            void createAnimation(Entity e, std::vector<sf::IntRect> frames);

            void setAnimationSpeed(Entity e, float speed);

            void setPlayingAnimation(Entity e, int index);

        private:
            std::shared_ptr<sf::RenderWindow> _window;
    };

}

#endif /* !SPRITESYSTEM_HPP_ */

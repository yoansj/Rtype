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

            bool initSprite(Entity e, std::string const &filepath, bool isAnimated);

            void createAnimation(Entity e, sf::IntRect rect);

            void changeTexture(Entity e, std::string const &filepath);

            void setScale(Entity e, int x, int y);

        private:
            std::shared_ptr<sf::RenderWindow> _window;
            sf::Clock _clock;
            sf::Time _time;
    };

}

#endif /* !SPRITESYSTEM_HPP_ */

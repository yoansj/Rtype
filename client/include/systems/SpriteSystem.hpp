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

            /**
             * @brief Update the Sprite System
             * 
             */
            void update();

            /**
             * @brief Init the Sprite with the Entity, the filepath and if is animated or not.
             * 
             * @param Entity e 
             * @param std::string const &filepath 
             * @param bool isAnimated 
             * @return bool 
             */
            bool initSprite(Entity e, std::string const &filepath, bool isAnimated);

            /**
             * @brief Create a Animation with the Entity set a Rect to the Entity.
             * 
             * @param Entity e 
             * @param sf::IntRect rect 
             */
            void createAnimation(Entity e, sf::IntRect rect);

            /**
             * @brief Change the texture to a Entity.
             * 
             * @param Entity e 
             * @param std::string const &filepath 
             */
            void changeTexture(Entity e, std::string const &filepath);

            /**
             * @brief Set the Scale to a Entity
             * 
             * @param Entity e 
             * @param int x 
             * @param int y 
             */
            void setScale(Entity e, int x, int y);

            /**
             * @brief Set the Rect to a Entity
             * 
             * @param Entity e 
             * @param sf::IntRect rect 
             */
            void setRect(Entity e, sf::IntRect rect);

            void setPath(Entity e, std::string const &filepath);

        private:
            std::shared_ptr<sf::RenderWindow> _window;
            sf::Clock _clock;
            sf::Time _time;
    };

}

#endif /* !SPRITESYSTEM_HPP_ */

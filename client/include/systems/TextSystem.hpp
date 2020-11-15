/*
** EPITECH PROJECT, 2020
** client
** File description:
** TextSystem
*/

#ifndef TEXTSYSTEM_HPP_
#define TEXTSYSTEM_HPP_

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

#include "System.hpp"
#include "Text.hpp"
#include "EngineError.hpp"

namespace Engine {

    /**
     * @brief  Sprite system used on the Sprite component
     */
    class TextSystem : public System<Text> {
        public:
            TextSystem();
            ~TextSystem() = default;

            /**
             * @brief Update the system.
             * 
             */
            void update();

            /**
             * @brief Init a text from a Entity
             * 
             * @param Entity e 
             * @param std::string const &text 
             * @param int size 
             * @return bool 
             */
            bool initText(Entity e, std::string const &text, int size);

            /**
             * @brief Set the Text to a Entity
             * 
             * @param Entity e 
             * @param std::string str 
             */
            void setText(Entity e, std::string str);

        private:
            std::shared_ptr<sf::RenderWindow> _window;
    };

}

#endif /* !TEXTSYSTEM_HPP_ */

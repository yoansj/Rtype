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

            void update();

            bool initText(Entity e, std::string const &filepath, int size);

        private:
            std::shared_ptr<sf::RenderWindow> _window;
    };

}

#endif /* !TEXTSYSTEM_HPP_ */

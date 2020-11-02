/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Window.hpp>

namespace Engine {
    class Engine {
        public:
            Engine();
            ~Engine();

            void update();
        protected:
        private:
            sf::Window _window;
            sf::Event _event;
    };
}

#endif /* !ENGINE_HPP_ */

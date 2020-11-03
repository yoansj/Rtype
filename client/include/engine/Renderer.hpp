/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "SystemManager.hpp"

namespace Engine {
    class Renderer {
        public:
            Renderer(const std::shared_ptr<sf::RenderWindow> &window);
            ~Renderer() = default;

            void doRender(SystemManager &sys);
        protected:
        private:
            std::shared_ptr<sf::RenderWindow> _window;
    };
}

#endif /* !RENDERER_HPP_ */

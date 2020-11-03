/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include "SystemManager.hpp"
#include "Entity.hpp"

namespace Engine {
    class Engine {
        public:
            Engine();
            ~Engine();

            void run();

            void updateSystems();
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            sf::Event _event;
            SystemManager _systems;
            EntityManager _entityManager;
    };
}

#endif /* !ENGINE_HPP_ */

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
#include "Renderer.hpp"

namespace Engine {

    using monsterGenerator = Entity (*) (EntityManager &, SystemManager &);

    class Engine {
        public:
            Engine();
            ~Engine();

            void initGame();

            void run();

            void updateSystems();
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            sf::Event _event;
            SystemManager _systems;
            EntityManager _entityManager;
            Renderer _renderer;
    };
}

#endif /* !ENGINE_HPP_ */

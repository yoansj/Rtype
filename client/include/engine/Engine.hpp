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
#include "SceneManager.hpp"
#include "Entity.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"

#include "Packages.hpp"
#include "PackagesType.hpp"

namespace Engine {

    using monsterGenerator = Entity (*) (EntityManager &, SystemManager &);

    class Engine {
        public:
            Engine(std::string const &serverIp);
            ~Engine();
            void run();

            void updateSystems();
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            sf::Event _event;
            SystemManager _systems;
            EntityManager _entityManager;
            Renderer _renderer;
            SceneManager _sceneManager;
            std::string _serverIp;
    };
}

#endif /* !ENGINE_HPP_ */

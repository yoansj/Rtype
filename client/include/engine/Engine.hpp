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

    /**
     * @brief Game Engine
     * 
     */
    class Engine {
        public:
            /**
             * @brief Construct a new Engine object.
             * 
             * @param std::string const & serverIp 
             */
            Engine(std::string const &serverIp);
            ~Engine();

            /**
             * @brief Loop for the game Engine.
             * 
             */
            void run();

            /**
             * @brief Update all systems.
             * 
             */
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

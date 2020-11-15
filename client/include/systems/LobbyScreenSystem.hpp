/*
** EPITECH PROJECT, 2020
** client
** File description:
** LobbyScreenSystem
*/

#ifndef LOBBYSCREENSYSTEM_HPP_
#define LOBBYSCREENSYSTEM_HPP_

#include "System.hpp"
#include "Position.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Entity.hpp"
#include "SpriteSystem.hpp"
#include "VelocitySystem.hpp"
#include "PositionSystem.hpp"
#include "ParallaxSystem.hpp"
#include "TextSystem.hpp"
#include "NetworkSystem.hpp"
#include <array>

#include <functional>

namespace Engine {
    /**
     * @brief Lobby System Screen to manage the scene Lobby.
     * 
     */
    class LobbyScreenSystem {
        enum choice {
            CREATE,
            JOIN,
            QUIT
        };
        public:
            /**
             * @brief Construct a new Lobby Screen System object
             * 
             * @param SpriteSystem &spriteSystem 
             * @param VelocitySystem &velocitySystem 
             * @param PositionSystem &positionSystem 
             * @param ParallaxSystem &parallaxSystem 
             * @param TextSystem &textSystem 
             * @param NetworkSystem &networkSystem 
             */
            LobbyScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem, ParallaxSystem &parallaxSystem, TextSystem &textSystem,
            NetworkSystem &networkSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _parallaxSystem(parallaxSystem), _textSystem(textSystem), _networkSystem(networkSystem),
            _created(false), _choice(choice::CREATE), _isPressed(true), _id(0) {};
            ~LobbyScreenSystem() = default;

            /**
             * @brief Create a Sprites with Entities
             * 
             * @param std::array<Entity, 2> parallax 
             * @param std::array<Entity, 3> buttons 
             * @param Entity text 
             */
            void createSprites(std::array<Entity, 2> parallax, std::array<Entity, 3> buttons, Entity text);

            /**
             * @brief Destroy a Sprites with the EntityManager
             * 
             * @param EntityManager &entityManager 
             */
            void destroySprites(EntityManager &entityManager);

            /**
             * @brief Check is the System is created
             * 
             * @return bool 
             */
            bool isCreated() const {return (_created);};

            /**
             * @brief Update the System.
             * 
             * @param EntityManager &entityManager 
             * @param SceneManager &sceneManager 
             * @param NetworkSystem &networkSystem 
             */
            void update(EntityManager &entityManager, SceneManager &sceneManager);

            /**
             * @brief Set the Id Game
             * 
             * @param int id 
             */
            void setId(int id) {_id = id;};

            /**
             * @brief Set the Has Focus object
             * 
             * @param std::function<bool()> f 
             */
            void setHasFocus(std::function<bool()> f) { _hasFocus = f;};

        protected:
        private:
            std::vector<Entity> _lobbyScreenEntities;
            bool _created;
            int _choice;
            bool _isPressed;
            int _id;
            SpriteSystem &_spriteSystem;
            VelocitySystem &_velocitySystem;
            PositionSystem &_positionSystem;
            ParallaxSystem &_parallaxSystem;
            TextSystem &_textSystem;
            NetworkSystem &_networkSystem;
            std::function<bool()> _hasFocus;
    };
}

#endif /* !LOBBYSCREENSYSTEM_HPP_ */

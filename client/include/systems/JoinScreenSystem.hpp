/*
** EPITECH PROJECT, 2020
** client
** File description:
** JoinScreenSystem
*/

#ifndef JoinScreenSystem_HPP_
#define JoinScreenSystem_HPP_

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
     * @brief Join Screen System to manage the scene Join
     * 
     */
    class JoinScreenSystem {
        enum choice {
            CREATE,
            JOIN,
            QUIT
        };
        public:
            /**
             * @brief Construct a new Join Screen System object
             * 
             * @param SpriteSystem &spriteSystem 
             * @param VelocitySystem &velocitySystem 
             * @param PositionSystem &positionSystem 
             * @param ParallaxSystem &parallaxSystem 
             * @param TextSystem &textSystem 
             */
            JoinScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem, ParallaxSystem &parallaxSystem, TextSystem &textSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _parallaxSystem(parallaxSystem), _textSystem(textSystem),
            _created(false), _choice(choice::CREATE), _isPressed(false), _id(0) {};
            ~JoinScreenSystem() = default;

            /**
             * @brief Create a Sprites Entity
             * 
             * @param std::array<Entity, 2> parallax 
             * @param std::array<Entity, 3> buttons 
             * @param Entity text 
             */
            void createSprites(std::array<Entity, 2> parallax, std::array<Entity, 3> buttons, Entity text);

            /**
             * @brief Destroy a Sprites Entity
             * 
             * @param EntityManager &entityManager 
             */
            void destroySprites(EntityManager &entityManager);

            /**
             * @brief Check if the game is created.
             * 
             * @return bool 
             */
            bool isCreated() const {return (_created);};

            /**
             * @brief Update the scene Join Screen System.
             * 
             * @param EntityManager &entityManager 
             * @param SceneManager &sceneManager 
             * @param NetworkSystem &networkSystem 
             */
            void update(EntityManager &entityManager, SceneManager &sceneManager, NetworkSystem &networkSystem);

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
            std::function<bool()> _hasFocus;
    };
}

#endif /* !JoinScreenSystem_HPP_ */

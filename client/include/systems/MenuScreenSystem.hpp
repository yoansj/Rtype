/*
** EPITECH PROJECT, 2020
** client
** File description:
** MenuScreenSystem
*/

#ifndef MENUSCREENSYSTEM_HPP_
#define MENUSCREENSYSTEM_HPP_

#include "System.hpp"
#include "Position.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Entity.hpp"
#include "SpriteSystem.hpp"
#include "VelocitySystem.hpp"
#include "PositionSystem.hpp"
#include "ParallaxSystem.hpp"
#include "SoundSystem.hpp"
#include "NetworkSystem.hpp"
#include <array>

#include <functional>


namespace Engine {
    /**
     * @brief Menu Screen System to manage the scene Menu.
     * 
     */
    class MenuScreenSystem {
        enum choice {
            CREATE,
            JOIN,
            QUIT
        };
        public:
            /**
             * @brief Construct a new Menu Screen System object
             * 
             * @param SpriteSystem &spriteSystem 
             * @param VelocitySystem &velocitySystem 
             * @param PositionSystem &positionSystem 
             * @param ParallaxSystem &parallaxSystem 
             */
            MenuScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem, ParallaxSystem &parallaxSystem, SoundSystem &soundSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _parallaxSystem(parallaxSystem), _soundSystem(soundSystem) ,_created(false), _choice(choice::CREATE), _isPressed(true) {};
            ~MenuScreenSystem() = default;

            /**
             * @brief Create a Sprites object
             * 
             * @param std::array<Entity, 2> parallax 
             * @param std::array<Entity, 3> buttons 
             */
            void createSprites(std::array<Entity, 2> parallax, std::array<Entity, 3> buttons, Entity sound);

            /**
             * @brief Destroy a Sprites object
             * 
             * @param EntityManager &entityManager 
             */
            void destroySprites(EntityManager &entityManager);

            /**
             * @brief Check is the Screen is created
             * 
             * @return bool 
             */
            bool isCreated() const {return (_created);};

            /**
             * @brief Update the scene Lobby Screen System.
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

            void stopMenuMusic();
        protected:
        private:
            std::vector<Entity> _menuScreenEntities;
            bool _created;
            int _choice;
            bool _isPressed;
            SpriteSystem &_spriteSystem;
            VelocitySystem &_velocitySystem;
            PositionSystem &_positionSystem;
            ParallaxSystem &_parallaxSystem;
            SoundSystem &_soundSystem;
            std::function<bool()> _hasFocus;
            Entity _soundEntity;
    };
}


#endif /* !MENUSCREENSYSTEM_HPP_ */
/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TitleScreenSystem
*/

#ifndef TITLESCREENSYSTEM_HPP_
#define TITLESCREENSYSTEM_HPP_

#include "System.hpp"
#include "Position.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Entity.hpp"
#include "SpriteSystem.hpp"
#include "VelocitySystem.hpp"
#include "PositionSystem.hpp"
#include <functional>

#include <vector>

namespace Engine {

    /**
     * @brief Title Screen Scene System
     */
    class TitleScreenSystem {
        public:
            /**
             * @brief Construct a new Title Screen System object
             * 
             * @param SpriteSystem &spriteSystem 
             * @param VelocitySystem &velocitySystem 
             * @param PositionSystem &positionSystem 
             */
            TitleScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _created(false) {};
            ~TitleScreenSystem() = default;

            /**
             * @brief Create a Sprites with Entities
             * 
             * @param Entity background
             * @param Entity logo
             * @param Entity text
             */
            void createSprites(Entity background, Entity logo);

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
             * @brief Update the system.
             * 
             * @param EntityManager &entityManager
             * @param SceneManager &sceneManager
             */
            void update(EntityManager &entityManager, SceneManager &sceneManager);

            /**
             * @brief Set the Has Focus object
             * 
             * @param std::function<bool()> f 
             */
            void setHasFocus(std::function<bool()> f) { _hasFocus = f;};
        private:
            std::vector<Entity> _titleScreenEntities;
            bool _created;

            SpriteSystem &_spriteSystem;
            VelocitySystem &_velocitySystem;
            PositionSystem &_positionSystem;
            std::function<bool()> _hasFocus;
    };

}

#endif /* !TITLESCREENSYSTEM_HPP_ */

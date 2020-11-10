/*
** EPITECH PROJECT, 2020
** client
** File description:
** GameScreenSystem
*/

#ifndef GAMESCREENSYSTEM_HPP_
#define GAMESCREENSYSTEM_HPP_

#include "System.hpp"
#include "Position.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Entity.hpp"
#include "SpriteSystem.hpp"
#include "VelocitySystem.hpp"
#include "PositionSystem.hpp"
#include "ParallaxSystem.hpp"

namespace Engine {
    class GameScreenSystem {
        public:
            GameScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem, ParallaxSystem &parallaxSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _parallaxSystem(parallaxSystem), _created(false) {};
            ~GameScreenSystem();

            void createSprites(Entity parallax);
            void destroySprites(EntityManager &entityManager);

            bool isCreated() const {return (_created);};
            void update(EntityManager &entityManager, SceneManager &sceneManager);

        protected:
        private:
            std::vector<Entity> _gameScreenEntities;
            bool _created;
            SpriteSystem &_spriteSystem;
            VelocitySystem &_velocitySystem;
            PositionSystem &_positionSystem;
            ParallaxSystem &_parallaxSystem;
    };
}

#endif /* !GAMESCREENSYSTEM_HPP_ */

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
#include <array>

namespace Engine {
    class MenuScreenSystem {
        enum choice {
            CREATE,
            JOIN,
            QUIT
        };
        public:
            MenuScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem, ParallaxSystem &parallaxSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _parallaxSystem(parallaxSystem), _created(false), _choice(choice::CREATE), _isPressed(false) {};
            ~MenuScreenSystem() = default;

            void createSprites(Entity parallax, std::array<Entity, 3> buttons);
            void destroySprites(EntityManager &entityManager);

            bool isCreated() const {return (_created);};
            void update(EntityManager &entityManager, SceneManager &sceneManager);

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
    };
}


#endif /* !MENUSCREENSYSTEM_HPP_ */
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
#include "NetworkSystem.hpp"
#include <array>

#include <functional>


namespace Engine {
    class MenuScreenSystem {
        enum choice {
            CREATE,
            JOIN,
            QUIT
        };
        public:
            MenuScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem, ParallaxSystem &parallaxSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _parallaxSystem(parallaxSystem), _created(false), _choice(choice::CREATE), _isPressed(true) {};
            ~MenuScreenSystem() = default;

            void createSprites(std::array<Entity, 2> parallax, std::array<Entity, 3> buttons);
            void destroySprites(EntityManager &entityManager);

            bool isCreated() const {return (_created);};
            void update(EntityManager &entityManager, SceneManager &sceneManager, NetworkSystem &networkSystem);

            void setHasFocus(std::function<bool()> f) { _hasFocus = f;};
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
            std::function<bool()> _hasFocus;
    };
}


#endif /* !MENUSCREENSYSTEM_HPP_ */
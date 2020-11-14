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
            TitleScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _created(false) {};
            ~TitleScreenSystem() = default;

            void createSprites(Entity background, Entity logo);
            void destroySprites(EntityManager &entityManager);

            bool isCreated() const {return (_created);};
            void update(EntityManager &entityManager, SceneManager &sceneManager);

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

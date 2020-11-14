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
#include "PackagesType.hpp"
#include "Packages.hpp"

#include <functional>

namespace Engine {
    class GameScreenSystem {
        public:
            GameScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem, ParallaxSystem &parallaxSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _parallaxSystem(parallaxSystem), _created(false)
            , _createdAllPlayers(false) {};
            ~GameScreenSystem() = default;

            void createSprites(std::array<Entity, 2> parallax);
            void destroySprites(EntityManager &entityManager);
            void initGame();

            bool isCreated() const {return (_created);};
            void update(EntityManager &entityManager, SceneManager &sceneManager);

            // Shortcuts functions
            void setPlayerIdF(std::function<std::size_t()> f) {_getPlayerId = f;};
            void setPlayerNbF(std::function<std::size_t()> f) {_getPlayerNb = f;};
            void setCreateEntityF(std::function<Entity()> f) {_createEntity = f;};
            void setSendPakageF(std::function<void(void const *package, int typePackage)> f) {_sendPackage = f;};
            void setGameIdF(std::function<std::size_t()> f) {_getGameId = f;};

        protected:
        private:
            std::vector<Entity> _gameScreenEntities;
            bool _created;
            std::vector<Entity> _playerEntities;
            bool _createdAllPlayers;

            // Systems
            SpriteSystem &_spriteSystem;
            VelocitySystem &_velocitySystem;
            PositionSystem &_positionSystem;
            ParallaxSystem &_parallaxSystem;

            // Shortcut functions
            std::function<std::size_t()> _getPlayerId;
            std::function<std::size_t()> _getPlayerNb;
            std::function<std::size_t()> _getGameId;
            std::function<void(void const *package, int typePackage)> _sendPackage;
            std::function<Entity()> _createEntity;
    };
}

#endif /* !GAMESCREENSYSTEM_HPP_ */

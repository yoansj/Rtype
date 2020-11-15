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

    /**
     * @brief Game Screen System, display and manage the lobby.
     * 
     */
    class GameScreenSystem {
        public:
            /**
             * @brief Construct a new Game Screen System object
             * 
             * @param SpriteSystem &spriteSystem 
             * @param VelocitySystem &velocitySystem 
             * @param PositionSystem &positionSystem 
             * @param ParallaxSystem &parallaxSystem 
             */
            GameScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem, ParallaxSystem &parallaxSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _parallaxSystem(parallaxSystem), _created(false)
            , _createdAllPlayers(false), shooting(false) {};
            ~GameScreenSystem() = default;

            /**
             * @brief Create a Sprites with Entities
             * 
             * @param std::array<Entity, 2> parallax 
             */
            void createSprites(std::array<Entity, 2> parallax);

            /**
             * @brief Destroy a Sprites Entity
             * 
             * @param EntityManager &entityManager 
             */
            void destroySprites(EntityManager &entityManager);

            /**
             * @brief Init the game.
             * 
             */
            void initGame();

            /**
             * @brief Check if the Entity is created.
             * 
             * @return bool 
             */
            bool isCreated() const {return (_created);};

            /**
             * @brief Update EntityManager and SceneManager.
             * 
             * @param EntityManager &entityManager 
             * @param SceneManager &sceneManager 
             */
            void update(EntityManager &entityManager, SceneManager &sceneManager);

            /**
             * @brief Update the players positions.
             * 
             * @param std::size_t index 
             * @param Position pos 
             */
            void updatePlayerPosition(std::size_t index, Position pos);

            // Shortcuts functions

            /**
             * @brief Set the Player Id F object
             * 
             * @param std::function<std::size_t()> f 
             */
            void setPlayerIdF(std::function<std::size_t()> f) {_getPlayerId = f;};

            /**
             * @brief Set the Player Nb F object
             * 
             * @param std::function<std::size_t()> f 
             */

            /**
             * @brief Set the Player Nb F object
             * 
             * @param std::function<std::size_t()> f 
             */
            void setPlayerNbF(std::function<std::size_t()> f) {_getPlayerNb = f;};

            /**
             * @brief Set the Create Entity F object
             * 
             * @param std::function<Entity()> f 
             */
            void setCreateEntityF(std::function<Entity()> f) {_createEntity = f;};

            /**
             * @brief Set the Send Pakage F object
             * 
             * @param std::function<void(char const *package, int typePackage)> f
             */
            void setSendPakageF(std::function<void(char const *package, int typePackage)> f) {_sendPackage = f;};

            /**
             * @brief Set the Game Id F object
             * 
             * @param std::function<std::size_t()> f 
             */
            void setGameIdF(std::function<std::size_t()> f) {_getGameId = f;};

            /**
             * @brief Set the Has Focus object
             * 
             * @param std::function<bool()> f 
             */
            void setHasFocus(std::function<bool()> f) { _hasFocus = f;};

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
            std::function<void(char const *package, int typePackage)> _sendPackage;
            std::function<Entity()> _createEntity;
            std::function<bool()> _hasFocus;

            //Misc
            bool shooting;
    };
}

#endif /* !GAMESCREENSYSTEM_HPP_ */

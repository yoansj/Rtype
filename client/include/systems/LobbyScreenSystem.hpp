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
    class LobbyScreenSystem {
        enum choice {
            CREATE,
            JOIN,
            QUIT
        };
        public:
            LobbyScreenSystem(SpriteSystem &spriteSystem, VelocitySystem &velocitySystem, PositionSystem &positionSystem, ParallaxSystem &parallaxSystem, TextSystem &textSystem,
            NetworkSystem &networkSystem) :
            _spriteSystem(spriteSystem), _velocitySystem(velocitySystem), _positionSystem(positionSystem), _parallaxSystem(parallaxSystem), _textSystem(textSystem), _networkSystem(networkSystem),
            _created(false), _choice(choice::CREATE), _isPressed(true), _id(0) {};
            ~LobbyScreenSystem() = default;

            void createSprites(std::array<Entity, 2> parallax, std::array<Entity, 3> buttons, Entity text);
            void destroySprites(EntityManager &entityManager);

            bool isCreated() const {return (_created);};
            void update(EntityManager &entityManager, SceneManager &sceneManager);
            void setId(int id) {_id = id;};

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

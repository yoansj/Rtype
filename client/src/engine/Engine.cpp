/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Engine
*/

#include "Engine.hpp"
#include <fstream>

Engine::Engine::Engine(std::string const &serverIp) :
    _window(std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type")),
    _renderer(_window), _serverIp(serverIp)
{
    _systems.networkSystem.setRecipient(serverIp);
    _systems.networkSystem.setDestroyLobby([this]() {
        this->_systems.lobbyScreen.destroySprites(this->_entityManager);
    });
    _systems.gameScreen.setPlayerIdF([this]() {
        return (this->_systems.networkSystem.getPlayerId());
    });
    _systems.gameScreen.setPlayerNbF([this]() {
        return (this->_systems.networkSystem.getPlayerNb());
    });
    _systems.gameScreen.setCreateEntityF([this]() {
        return (this->_entityManager.create());
    });
    _systems.gameScreen.setSendPakageF([this](const char *p, int tp) {
        this->_systems.networkSystem.sendPackage(p, tp);
    });
    _systems.gameScreen.setGameIdF([this]() {
        return (this->_systems.networkSystem.getIdGame());
    });
    _systems.titleScreen.setHasFocus([this]() {
        return (this->_window->hasFocus());
    });
    _systems.menuScreen.setHasFocus([this]() {
        return (this->_window->hasFocus());
    });
    _systems.lobbyScreen.setHasFocus([this]() {
        return (this->_window->hasFocus());
    });
    _systems.joinScreen.setHasFocus([this]() {
        return (this->_window->hasFocus());
    });
    _systems.gameScreen.setHasFocus([this]() {
        return (this->_window->hasFocus());
    });
    _systems.networkSystem.setGameUpdatePlayerPos([this](std::size_t index, Position pos) {
        this->_systems.gameScreen.updatePlayerPosition(index, pos);
    });
}

Engine::Engine::~Engine()
{
}

/**
 * @brief  This function runs the engine
 * @returns None
 */
void Engine::Engine::run()
{
    sf::Clock clock;

    while (_window->isOpen()) {
        _window->clear(sf::Color::Black);
        _systems.networkSystem.update(_sceneManager, _entityManager);
        while (_window->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                _window->close();
        }
        if (clock.getElapsedTime().asMilliseconds() >= 1000.0 / 60.0) {
            updateSystems();
            _renderer.doRender(_systems);
            _window->display();
            clock.restart();
        }
    }
}

/**
 * @brief  This function is used to update all systems
 * @retval None
 */
void Engine::Engine::updateSystems()
{
    if (_sceneManager.getScene() == SCENE::TITLE_SCREEN) {
        if (!_systems.titleScreen.isCreated()) {
            _systems.titleScreen.createSprites(_entityManager.create(), _entityManager.create());
        }
        _systems.titleScreen.update(_entityManager, _sceneManager);
    }
    if (_sceneManager.getScene() == SCENE::GAME) {
        if (!_systems.gameScreen.isCreated()) {
            _systems.gameScreen.createSprites({_entityManager.create(), _entityManager.create() });
        }
        _systems.gameScreen.update(_entityManager, _sceneManager);
    }
    if (_sceneManager.getScene() == SCENE::MAIN_MENU) {
        if (!_systems.menuScreen.isCreated()) {
            _systems.menuScreen.createSprites({_entityManager.create(), _entityManager.create() }, {_entityManager.create(), _entityManager.create(), _entityManager.create()});
        }
        _systems.menuScreen.update(_entityManager, _sceneManager, _systems.networkSystem);
    }
    if (_sceneManager.getScene() == SCENE::JOIN_GAME) {
        if (!_systems.joinScreen.isCreated()) {
            _systems.joinScreen.createSprites({_entityManager.create(), _entityManager.create() }, {_entityManager.create(), _entityManager.create(), _entityManager.create()}, _entityManager.create());
        }
        _systems.joinScreen.update(_entityManager, _sceneManager, _systems.networkSystem);
    } else if (_sceneManager.getScene() != SCENE::JOIN_GAME && _systems.joinScreen.isCreated())
        _systems.joinScreen.destroySprites(_entityManager);
    if (_sceneManager.getScene() == SCENE::LOBBY) {
        if (!_systems.lobbyScreen.isCreated()) {
            _systems.lobbyScreen.createSprites({_entityManager.create(), _entityManager.create() }, {_entityManager.create(), _entityManager.create(), _entityManager.create()}, _entityManager.create());
        }
        _systems.lobbyScreen.update(_entityManager, _sceneManager);
    }
    if (_sceneManager.getScene() == SCENE::GAME_END)
            _window->close();
    _systems.lobbyScreen.setId(_systems.networkSystem.getIdGame());

    /*auto player = _systems.playerSystem.getPlayer();
    auto bgEntity = _systems.parallaxSystem.getBackgroundEntity();
    _systems.positionSystem.update();
    _systems.spriteSystem.update();
    _systems.parallaxSystem.update(_systems.positionSystem.getComponent(bgEntity), _systems.velocitySystem.getComponent(bgEntity));
    _systems.inputSystem.update(_systems.positionSystem.getComponent(player), _systems.velocitySystem.getComponent(player), _systems.spriteSystem.getComponent(player));*/
}
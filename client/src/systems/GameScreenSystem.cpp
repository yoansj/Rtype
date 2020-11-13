/*
** EPITECH PROJECT, 2020
** client
** File description:
** GameScreenSystem
*/

#include "GameScreenSystem.hpp"

void Engine::GameScreenSystem::createSprites(std::array<Entity, 2> parallax)
{
    _spriteSystem.create(parallax[0]);
    _positionSystem.create(parallax[0]);
    _positionSystem.setPosition(parallax[0], 0, 0);
    _spriteSystem.initSprite(parallax[0], "../client/assets/parallax.png", false);
    _velocitySystem.create(parallax[0]);
    _velocitySystem.setVelocity(parallax[0], 3, 3);
    _parallaxSystem.setBackgroundEntity(parallax[0]);

    _spriteSystem.create(parallax[1]);
    _positionSystem.create(parallax[1]);
    _positionSystem.setPosition(parallax[1], 3840, 0);
    _spriteSystem.initSprite(parallax[1], "../client/assets/parallax.png", false);
    _velocitySystem.create(parallax[1]);
    _velocitySystem.setVelocity(parallax[1], 3, 3);
    _parallaxSystem.setBackgroundEntity(parallax[1]);


    _gameScreenEntities.push_back(parallax[0]);
    _gameScreenEntities.push_back(parallax[1]);
    _created = true;
}

void Engine::GameScreenSystem::destroySprites(EntityManager &entityManager)
{
    for (int i = 0; i != _gameScreenEntities.size(); i++) {
        _spriteSystem.destroy(_gameScreenEntities[i]);
        _velocitySystem.destroy(_gameScreenEntities[i]);
        _positionSystem.destroy(_gameScreenEntities[i]);
        //_parallaxSystem.destroy(_gameScreenEntities[i]);
        entityManager.remove(_gameScreenEntities[i]);
    }
    _created = false;
}

void Engine::GameScreenSystem::update(EntityManager &entityManager, SceneManager &sceneManager)
{
    _parallaxSystem.update(_positionSystem.getComponent(_gameScreenEntities[0]), _velocitySystem.getComponent(_gameScreenEntities[0]));
    _parallaxSystem.update(_positionSystem.getComponent(_gameScreenEntities[1]), _velocitySystem.getComponent(_gameScreenEntities[1]));
}
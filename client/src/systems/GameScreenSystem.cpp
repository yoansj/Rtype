/*
** EPITECH PROJECT, 2020
** client
** File description:
** GameScreenSystem
*/

#include "GameScreenSystem.hpp"

void Engine::GameScreenSystem::createSprites(Entity parallax)
{
    _spriteSystem.create(parallax);
    _positionSystem.create(parallax);
    _positionSystem.setPosition(parallax, -1800, 0);
    _spriteSystem.initSprite(parallax, "../client/assets/background.png", false);
    _velocitySystem.create(parallax);
    _velocitySystem.setVelocity(parallax, 1, 1);
    _parallaxSystem.setBackgroundEntity(parallax);
    _spriteSystem.createAnimation(parallax, sf::IntRect(400, 0, 300, 400));

    _gameScreenEntities.push_back(parallax);
    _created = true;
}

void Engine::GameScreenSystem::destroySprites(EntityManager &entityManager)
{
    for (int i = 0; i != _gameScreenEntities.size(); i++) {
        _spriteSystem.destroy(_gameScreenEntities[i]);
        _velocitySystem.destroy(_gameScreenEntities[i]);
        _positionSystem.destroy(_gameScreenEntities[i]);
        _parallaxSystem.destroy(_gameScreenEntities[i]);
        entityManager.remove(_gameScreenEntities[i]);
    }
    _created = false;
}

void Engine::GameScreenSystem::update(EntityManager &entityManager, SceneManager &sceneManager)
{
    _parallaxSystem.update(_positionSystem.getComponent(_gameScreenEntities[0]), _velocitySystem.getComponent(_gameScreenEntities[0]));

}
/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TitleScreenSystem
*/

#include "TitleScreenSystem.hpp"


void Engine::TitleScreenSystem::createSprites(Entity background, Entity logo)
{
    _spriteSystem.create(background);
    _velocitySystem.create(background);
    _positionSystem.create(background);
    _spriteSystem.initSprite(background, "../client/assets/titlebg.jpg", false);
    _positionSystem.setPosition(background, 0, 0);
    _velocitySystem.setVelocity(background, 0, 0);

    _spriteSystem.create(logo);
    _velocitySystem.create(logo);
    _positionSystem.create(logo);
    _spriteSystem.initSprite(logo, "../client/assets/rtypelogo.png", false);
    _positionSystem.setPosition(logo, 420, 360);
    _velocitySystem.setVelocity(logo, 0, 0);

    _titleScreenEntities.push_back(logo);
    _titleScreenEntities.push_back(background);
    _created = true;
}

void Engine::TitleScreenSystem::destroySprites(EntityManager &entityManager)
{
    for (int i = 0; i != _titleScreenEntities.size(); i++) {
        _spriteSystem.destroy(_titleScreenEntities[i]);
        _velocitySystem.destroy(_titleScreenEntities[i]);
        _positionSystem.destroy(_titleScreenEntities[i]);
        entityManager.remove(_titleScreenEntities[i]);
    }
    _created = false;
}

void Engine::TitleScreenSystem::update(EntityManager &entityManager, SceneManager &sceneManager)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        destroySprites(entityManager);
        sceneManager.setScene(MAIN_MENU);
    }
}
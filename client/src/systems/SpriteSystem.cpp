/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SpriteSystem
*/

#include "SpriteSystem.hpp"

Engine::SpriteSystem::SpriteSystem() : System()
{
}

bool Engine::SpriteSystem::initSprite(Entity e, std::string const &filepath)
{
    auto component = _components.getComponent(e);

    if (!component.texture.loadFromFile(filepath)) {
        throw std::logic_error("blabla sprite a changer non trouvé");
    } else {
        component.sprite.setTexture(component.texture);
        component.isCreated = true;
    }
    return (true);
}

void Engine::SpriteSystem::update()
{
}

void Engine::SpriteSystem::setWindow(std::shared_ptr<sf::RenderWindow> const &window)
{
    _window = window;
}
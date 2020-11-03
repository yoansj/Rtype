/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SpriteSystem
*/

#include "SystemManager.hpp"
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
    for (int i = 0; i != _components.size(); i++) {
        auto entity = _components[i].entity;
        auto position = SystemManager::Get().positionSystem.getComponent(entity);
        _components.getComponents()[i].sprite.setPosition(20, 20);
        std::cout << _components.getComponents()[i].sprite.getPosition().x << std::endl;
        _window->draw(_components.getComponents()[i].sprite);
        std::cout << "draw !" << std::endl;
    }
}

void Engine::SpriteSystem::setWindow(std::shared_ptr<sf::RenderWindow> const &window)
{
    _window = window;
}
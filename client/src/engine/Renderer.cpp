/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Renderer
*/

#include "Renderer.hpp"

Engine::Renderer::Renderer(const std::shared_ptr<sf::RenderWindow> &window)
{
    _window = window;
}

void Engine::Renderer::doRender(SystemManager &sys)
{
    for (int i = 0; i != sys.spriteSystem.size(); i++) {
        auto entity = sys.spriteSystem.getComponents()[i].entity;
        auto const &position = sys.positionSystem.getComponent(entity);
        auto &sprite = sys.spriteSystem.getComponents()[i];
        sprite.sprite.setTexture(sprite.texture, true);
        sprite.sprite.setPosition(position.x, position.y);
        _window->draw(sprite.sprite);
    }
}


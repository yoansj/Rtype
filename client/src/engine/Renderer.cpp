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
        auto &position = sys.positionSystem.getComponent(entity);
        std::cout << "debug: " << position.x << " " << position.y << std::endl;
        sys.spriteSystem.getComponents()[i].sprite.setPosition(position.x, position.y);
        _window->draw(sys.spriteSystem.getComponents()[i].sprite);
    }
}


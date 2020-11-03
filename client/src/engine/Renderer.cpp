/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Renderer
*/

#include "Renderer.hpp"

Engine::Renderer::Renderer(const std::shared_ptr<sf::RenderWindow> &window) :
    _window(window)
{
}

Engine::Renderer::~Renderer()
{
}

void Engine::Renderer::doRender(SystemManager &sys)
{
    for (int i = 0; i != sys.spriteSystem.size(); i++) {
        auto entity = sys.spriteSystem.getComponents()[i].entity;
        auto position = sys.positionSystem.getComponent(entity);
        sys.spriteSystem.getComponents()[i].sprite.setPosition(20, 20);
        std::cout << sys.spriteSystem.getComponents()[i].sprite.getPosition().x << std::endl;
        _window->draw(sys.spriteSystem.getComponents()[i].sprite);
        std::cout << "draw !" << std::endl;
    }
}


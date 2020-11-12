/*
** EPITECH PROJECT, 2020
** client
** File description:
** TextSystem
*/

#include "TextSystem.hpp"

Engine::TextSystem::TextSystem() : System()
{
}


bool Engine::TextSystem::initText(Entity e, std::string const &text, int size)
{
    auto &component = _components.getComponent(e);

    component.font.loadFromFile("../client/assets/Roboto-Black.ttf");
    component.text.setFont(component.font);
    component.text.setString(text);
    component.text.setCharacterSize(size);
    component.text.setFillColor(sf::Color::White);
    return (true);

}

void Engine::TextSystem::update()
{
}

void Engine::TextSystem::setText(Entity e, std::string str)
{
    auto &component = _components.getComponent(e);

    component.text.setString(str);
}
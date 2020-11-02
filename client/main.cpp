/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** main
*/

#include <iostream>
#include <SFML/Window.hpp>
#include "PositionComponent.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "PositionSystem.hpp"

int main(int argc, char **argv)
{
	sf::Window window(sf::VideoMode(800, 600), "My window");
	sf::Event event;


	Client::Systems::SystemManager::Get().CreateSystem(
		// std::make_shared<Client::Systems::PositionSystem>()
		Client::Systems::PositionSystem()
	);

	Client::Components::ComponentManager::Get().CreateComponent(
		// std::make_shared<Client::Components::PositionComponent>(11, 12)
		Client::Components::PositionComponent(11,12)
	);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			Client::Systems::SystemManager::Get().Update();
		}
	}
	return 0;
}

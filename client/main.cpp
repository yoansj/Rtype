/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** main
*/

#include <iostream>
#include <SFML/Window.hpp>
#include "PositionComponent.hpp"
#include "Component.hpp"

int main(int argc, char **argv)
{
	sf::Window window(sf::VideoMode(800, 600), "My window");
	sf::Event event;
    Client::Components::PositionComponent pos(42, 0);

    std::cout << pos.x << std::endl;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}

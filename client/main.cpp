/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** main
*/

#include <iostream>
#include <SFML/Window.hpp>
#include "Entity.hpp"
#include "PositionSystem.hpp"


int main(int argc, char **argv)
{
	sf::Window window(sf::VideoMode(800, 600), "My window");
	sf::Event event;

	Engine::EntityManager E;
	Engine::PositionSystem Pos;


	Entity box = E.create();
	Entity otherbox = E.create();
	Entity ball = E.create();

	auto boxPos = Pos.create(box);
	auto ortherboxPos = Pos.create(otherbox);
	auto ballPos = Pos.create(ball);


	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}

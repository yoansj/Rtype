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
#include "Engine.hpp"


int main(int argc, char **argv)
{
	Engine::Engine game;

	try {
		game.run();
	} catch (...) {

	}
	return 0;
}

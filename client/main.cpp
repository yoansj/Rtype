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

	game.update();
	// Engine::EntityManager E;
	// Engine::PositionSystem Pos;


	// Entity box = E.create();
	// Entity otherbox = E.create();
	// Entity ball = E.create();

	// auto boxPos = Pos.create(box);
	// auto ortherboxPos = Pos.create(otherbox);
	// auto ballPos = Pos.create(ball);

	return 0;
}

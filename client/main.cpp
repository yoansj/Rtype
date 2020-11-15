/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** main
*/

#include <iostream>
#include <SFML/Window.hpp>
#include "Entity.hpp"
#include "PositionSystem.hpp"
#include "MonsterLoaderSystem.hpp"
#include "Engine.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
        std::cout << "Try : ./run_client <port>" << std::endl;
        return 0;
    }

	Engine::Engine game(argv[1]);

	try {
		game.run();
	} catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
	}
	return 0;
}
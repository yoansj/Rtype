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
#include "Engine.hpp"


// int main(int argc, char **argv)
// {
// 	Engine::Engine game;

// 	try {
// 		game.run();
// 	} catch (std::exception &e) {
//         std::cerr << e.what() << std::endl;
// 	}
// 	return 0;
// }


#include "UdpClient.hpp"
#include "Packages.hpp"
#include "PackagesType.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "Try : ./run_client <port>" << std::endl;
        return 0;
    }
    UdpClient client(std::atoi(argv[1]), "localhost");
    createNewGame_t package = {CREATE_NEW_GAME, "Connection"};

        client.sendPackage(static_cast<void *>(&package));
    while (1) {
        std::cout << client.receivePackage() << std::endl;
    }
    return 0;
}

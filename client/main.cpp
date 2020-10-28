/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** main
*/

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

int main(int argc, char **argv)
{
	sf::Window window(sf::VideoMode(800, 600), "My window");
	sf::Event event;
    sf::UdpSocket connectSocket;

	char toSend[100] = "yoannnnn";
    char data[100];

	std::size_t received;
    sf::IpAddress sender;
    unsigned short port;

    sf::IpAddress test = "127.0.0.1";

    connectSocket.setBlocking(false);
	if (connectSocket.bind(54000) != sf::Socket::Done) {
        std::cout << "Erreur de port" << std::endl;
        exit(42);
    }


	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
                connectSocket.unbind();
		}
        sf::Vector2i m = sf::Mouse::getPosition(window);
        void *mousePos = &m;

		if (connectSocket.send(mousePos, 100, test, 54000) != sf::Socket::Done) {
            std::cout << "Erreur d'envoi" << std::endl;
        }
        /*if (connectSocket.receive(data, 100, received, sender, port) != sf::Socket::Done) {
            std::cout << "Erreur de reçu" << std::endl;
        }*/
        if (data != nullptr) {
            //std::cout << data << std::endl;
        }
	}
	return 0;
}

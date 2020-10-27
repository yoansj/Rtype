/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-aurele.auboin
** File description:
** main
*/

#include "iostream"
#include <SFML/Network.hpp>

int main()
{
    char data[100];
	std::size_t received;
    sf::UdpSocket socket;
    sf::IpAddress sender;
    unsigned short port;

    socket.bind(54000);
    socket.setBlocking(false);

    while (1) {
        if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done ) {
            std::cout << "Erreur de paquets zebi" << std::endl;
        } else {
            std::cout << "Got : " << data << " from : " << sender << std::endl; 
        }
    }

    return (0);
}

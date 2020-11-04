/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** main
*/

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <string.h>

struct data {
    int type_message;
    int struct_type;
    char message[2000];
};


class udp_client {
    public:
        udp_client(unsigned port, sf::IpAddress recipient) {
            _recipient = recipient;
            _port = port;
        }

        void send(struct data *tmp) {
            _socket.send(tmp, sizeof(struct data), _recipient, _port);
        }

        std::string receiver(void) {
            char data[4096];
            std::size_t received;
            sf::IpAddress sender;
            unsigned short port;

            _socket.receive(data, 4096, received, sender, port);
            std::cout << std::string(&data[0], received) << std::endl;
            return std::string(&data[0], received);
        }
    private:
        sf::UdpSocket _socket;
        sf::IpAddress _recipient;
        unsigned short _port;
};

int main(int argc, char **argv)
{
    udp_client client(7171, "localhost");
    struct data tmp = {0, 0, "Move up"};

    client.send(&tmp);
    while (1) {
        client.receiver();
    }
    return 0;
}
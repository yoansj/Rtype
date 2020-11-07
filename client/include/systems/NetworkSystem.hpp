/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
#define NETWORKSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Position.hpp"
#include "System.hpp"
#include "Packages.hpp"
#include "EngineError.hpp"

namespace Engine {

    /**
     * @brief  Position system used on the Position component
     */
    class NetworkSystem : public System<Position> {
        public:
            NetworkSystem() : System() {_serverSocket.setBlocking(false);};
            ~NetworkSystem() = default;

            void send(void const *package);
            void setPort(unsigned short port) {_port = port;};
            void setRecipient(sf::IpAddress recipient) {_recipient = recipient;};
            void update() {};
            std::string receiveData();
        private:
            sf::UdpSocket _serverSocket;
            sf::IpAddress _recipient;
            unsigned short _port;
    };

}

#endif /* !NETWORKSYSTEM_HPP_ */

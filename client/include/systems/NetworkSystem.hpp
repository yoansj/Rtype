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
            NetworkSystem() : System() {
                _recipient = "localhost";
                _port = 7172;
                _connectedTcp = true;
                _socketTcp.connect(_recipient, _port);
                _socketTcp.setBlocking(false);
                _socketUdp.setBlocking(false);
            };
            ~NetworkSystem() = default;

            void sendPackage(void const *package, int typePackage);
            void setPort(unsigned short port) {_port = port;};
            void setRecipient(sf::IpAddress recipient) {_recipient = recipient;};
            void update() {};
            std::string receivePackage();
        private:
            sf::IpAddress _recipient;
            unsigned short _port;
            sf::UdpSocket _socketUdp;
            sf::TcpSocket _socketTcp;
            bool _connectedTcp;
    };

}

#endif /* !NETWORKSYSTEM_HPP_ */

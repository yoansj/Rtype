/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** PositionComponent
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include <iostream>
#include <string>
#include "Component.hpp"

namespace Client {

    namespace Components {

        class PositionComponent : public Client::Components::Component {
            public:
                PositionComponent(float setX, float setY) : Client::Components::Component("Position"), x(setX), y(setY) {};
                ~PositionComponent() {std::cout << "destruction";};

                float x;
                float y;
            protected:
            private:
        };

    }

}

#endif /* !POSITIONCOMPONENT_HPP_ */

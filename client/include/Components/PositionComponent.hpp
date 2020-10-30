/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** PositionComponent
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include "Component.hpp"
#include <iostream>
#include <string>

namespace Client {

    namespace Components {

        class PositionComponent : public Components::Component {
            public:
                PositionComponent(float setX, float setY) : Client::Components::Component("Position", -1, {"PositionSystem"}), x(setX), y(setY) {};
                ~PositionComponent() {};

                void print() {std::cout << x << " " << y << std::endl;};

                float x;
                float y;
            protected:
            private:
        };

    }

}

#endif /* !POSITIONCOMPONENT_HPP_ */

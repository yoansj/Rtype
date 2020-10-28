/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <string>

namespace Client {

    namespace Components {

        class Component {
            public:
                Component(std::string name) : _name(name) {};
                virtual ~Component() = 0;
            
                std::string _name;
        };

    }

}

#endif /* !COMPONENT_HPP_ */

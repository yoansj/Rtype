/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <iostream>
#include <string>
#include <vector>

namespace Client {

    namespace Components {

        class Component {
            public:
                Component(std::string name, int id, std::vector<std::string> systems)
                : _name(name), _entityId(id), _systems(systems) {};
                virtual ~Component();
            
                std::string _name;
                int _entityId;
                std::vector<std::string> _systems;
        };

    }

}

#endif /* !COMPONENT_HPP_ */

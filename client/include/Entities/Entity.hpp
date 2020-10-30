/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <vector>

#include "Component.hpp"

namespace Client {

    namespace Entities {

        class Entity {
            public:
                Entity(int id, std::vector<Components::Component> initComponents) : _id(id), _components(initComponents) {}
                ~Entity() {};

            private:
                int _id;
                std::vector<Components::Component> _components;
        };

    }

}

#endif /* !ENTITY_HPP_ */

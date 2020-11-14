/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "Entity.hpp"

namespace Engine {

    /**
     * @brief  Base class for all of our components
     * A component is a data structure that belongs to an entity
     * All components must inherit this class
     */
    class Component {
        public:
            Component(Entity father) : entity(father) {};
            Component() {};
            ~Component() = default;
            Entity entity;
    };

}

#endif /* !COMPONENT_HPP_ */

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
            Component(Entity father) : _entity(father) {};
            ~Component() = default;
            Entity getEntity() {return (_entity);};

        protected:
            Entity _entity;
    };

}

#endif /* !COMPONENT_HPP_ */

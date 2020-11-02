/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "ComponentManager.hpp"

template<class AbstractComponent>
class System {
    public:
        System() = default;
        ~System() = default;

        AbstractComponent &create(Entity e) {
            return (_components.create(e));
        }

        bool destroy(Entity e) {
            return (_components.destroy(e));
        }

        AbstractComponent &getComponent(Entity e) {
            return (_components.getComponent(e));
        }

    protected:
        ComponentManager<AbstractComponent> _components;
};

#endif /* !SYSTEM_HPP_ */

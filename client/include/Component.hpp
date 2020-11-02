/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "Entity.hpp"

class Component {
    public:
        Component();
        ~Component();

    protected:
        Entity _entity;
    private:
};

#endif /* !COMPONENT_HPP_ */

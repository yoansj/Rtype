/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

#include "Component.hpp"

namespace Engine {

    /**
     * @brief Component Velocity
     * 
     */
    struct Velocity : public Component {
        /**
         * @brief Construct a new Velocity object
         * 
         * @param Entity e 
         */
        Velocity(Entity e) : Component(e) {entity = e;};
        float x;
        float y;
    };

}


#endif /* !VELOCITY_HPP_ */

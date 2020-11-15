/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Status
*/

#ifndef STATUS_HPP_
#define STATUS_HPP_

#include "Component.hpp"

namespace Engine {

    /**
     * @brief Enum to know the status of an entity.
     * 
     */
    enum StatusType {
        ALIVE,
        DEAD,
    };

    /**
     * @brief Status component.
     * 
     */
    struct Status : public Component {
        /**
         * @brief Construct a new Status object
         * 
         * @param Entity e 
         */
        Status(Entity e) : Component(e) {entity = e;};

        /**
         * @brief Construct a new Status object
         * 
         */
        Status() = default;
        StatusType type;
    };

}

#endif /* !STATUS_HPP_ */

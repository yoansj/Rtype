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

    enum StatusType {
        ALIVE,
        DEAD,
    };

    struct Status : public Component {
        Status(Entity e) : Component(e) {entity = e;};
        Status() = default;
        StatusType type;
    };

}

#endif /* !STATUS_HPP_ */

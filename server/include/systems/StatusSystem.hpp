/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** StatusSystem
*/

#ifndef STATUSSYSTEM_HPP_
#define STATUSSYSTEM_HPP_

#include "System.hpp"
#include "Status.hpp"

namespace Engine {

    /**
     * @brief  System used for collisions
     */
    class StatusSystem : public System<Status> {
        public:
            StatusSystem() : System() {};
            ~StatusSystem() = default;

            void update() override {};

            void setStatus(Entity e, StatusType type) {
                auto &hb = _components.getComponent(e);

                hb.type = type;
            }

            Status &getStatus(Entity e) {
                return (
                    _components.getComponent(e)
                );
            }
    };

}

#endif /* !STATUSSYSTEM_HPP_ */

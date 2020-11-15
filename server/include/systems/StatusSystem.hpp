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
            /**
             * @brief Construct a new Status System object
             * 
             */
            StatusSystem() : System() {};

            /**
             * @brief Destroy the Status System object
             * 
             */
            ~StatusSystem() = default;

            void update() override {};

            /**
             * @brief Set the Status Entity
             * 
             * @param params1 Entity e
             * @param params2 StatusType type
             */
            void setStatus(Entity e, StatusType type) {
                auto &hb = _components.getComponent(e);

                hb.type = type;
            }

            /**
             * @brief Get the Status Entity
             * 
             * @param params1 Entity e
             * @return value Status&
             */
            Status &getStatus(Entity e) {
                return (
                    _components.getComponent(e)
                );
            }
    };

}

#endif /* !STATUSSYSTEM_HPP_ */

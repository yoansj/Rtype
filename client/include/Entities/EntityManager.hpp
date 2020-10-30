/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <vector>
#include <memory>

#include "Component.hpp"
#include "Entity.hpp"

namespace Client {

    namespace Entities {

        class EntityManager {
            public:
                static EntityManager &Get() {static EntityManager instance; return (instance);};
                std::shared_ptr<Entity> &Create(std::vector<Components::Component> initComponents);

            private:
                EntityManager &operator= (const EntityManager&) = delete;
                EntityManager (const EntityManager&) = delete;
                EntityManager() : _minId(0) {};
                ~EntityManager() = default;

                std::vector<std::shared_ptr<Entity>> _entities;
                int _minId;
        };

    }

}

#endif /* !ENTITYMANAGER_HPP_ */

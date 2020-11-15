/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

typedef std::size_t Entity;

namespace Engine {

    /**
     * @brief Manager for Entity, create and remove.
     * 
     */
    class EntityManager {
        public:
            EntityManager() = default;
            ~EntityManager() = default;

            Entity create();
            bool remove(Entity e);
        private:

            std::vector<Entity> _entityList;

    };
}

#endif /* !ENTITY_HPP_ */

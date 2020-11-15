/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Entity
*/

#include "Entity.hpp"
/**
 * @brief Create a entity from the engine.
 * 
 * @return Entity 
 */
Entity Engine::EntityManager::create() {
    const auto it = std::adjacent_find(begin(_entityList), end(_entityList), [](Entity l, Entity r) { return (l+1 != r);});
    if (it == end(_entityList)) {
        _entityList.push_back(_entityList.size());
        return _entityList.back();
    } else {
        const auto result = _entityList.insert(it+1, (*it)+1);
        return *result;
    }
}

/**
 * @brief Remove a entity from the engine.
 * 
 * @param Entity e
 * @return bool 
 */
bool Engine::EntityManager::remove(Entity e) {
    const auto it = std::find(begin(_entityList), end(_entityList), e);
    if (it != end(_entityList)) {
        _entityList.erase(it);
        return (true);
    }
    return (false);
}


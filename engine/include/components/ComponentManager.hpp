/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include <vector>

#include "Entity.hpp"
#include "EngineError.hpp"
#include "Component.hpp"

/**
 * ComponentManager which manages the creation, destruction of components.
 */
template<class AbstractComponent>
class ComponentManager {
    public:
        ComponentManager() = default;
        ~ComponentManager() = default;

        /** Create Entity and return it.
            @param param1 Entity e
            @return value AbstractComponent
        */
        AbstractComponent &create(Entity e) {
            _components.push_back(AbstractComponent(e));
            _components.back().entity = e;
            return (_components.back());
        }

        /** Delete Entity and confirm deletion.
            @param param1 Entity &e
            @return value bool
        */
        bool destroy(Entity &e) {
            for (int i = 0; i != _components.size(); i++) {
                if (_components[i].entity == e) {
                    _components.erase(_components.begin() + i);
                    return (true);
                }
            }
            return (false);
        }

        /** Return the size of components.
            @return value size_t
        */
        size_t size() {return(_components.size());};

        AbstractComponent &getComponent(Entity &e) {
            for (int i = 0; i != _components.size(); i++) {
                if (_components[i].entity == e) {
                    return (_components[i]);
                }
            }
            throw EngineError("Component error", "Component not found {" + std::to_string(e) + "} !");
        }

        /** Return all the components.
            @return std::vector<AbstractComponent>
        */
        std::vector<AbstractComponent> &getComponents() {
            return (_components);
        }

        /** Check if a component entity exist.
         * @param param1 Entity e
         * @return value bool
        */
        bool Exist(Entity e) {
            for (int i = 0; i != _components.size(); i++) {
                if (_components[i].entity == e) {
                    return (true);
                }
            }
            return (false);
        }

    private:
        std::vector<AbstractComponent> _components;
};

#endif /* !COMPONENTMANAGER_HPP_ */

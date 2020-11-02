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
#include "Component.hpp"

template<class AbstractComponent>
class ComponentManager {
    public:
        ComponentManager() = default;
        ~ComponentManager() = default;

        AbstractComponent &create(Entity &e) {
            _components.push_back(AbstractComponent(e));
            std::cout << "Created component !" << std::endl;
            return (_components.back());
        }

        bool destroy(Entity &e) {
            for (int i = 0; i != _components.size(); i++) {
                if (_components[i].entity == e) {
                    _components.erase(_components.begin() + i);
                    return (true);
                }
            }
            return (false);
        }

        size_t size() {return(_components.size());};

        AbstractComponent &getComponent(Entity &e) {
            for (int i = 0; i != _components.size(); i++) {
                if (_components[i].entity == e) {
                    return (_components[i]);
                }
            }
            throw std::logic_error("Component non trouvé");
        }

        std::vector<AbstractComponent> &getComponents() {
            return (_components);
        }

        const AbstractComponent &operator[](std::size_t size) {
            return (_components[size]);
        }

    private:
        std::vector<AbstractComponent> _components;
};

#endif /* !COMPONENTMANAGER_HPP_ */

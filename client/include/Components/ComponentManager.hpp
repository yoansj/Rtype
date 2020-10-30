/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include <map>
#include <vector>

#include "SystemManager.hpp"
#include "Component.hpp"
#include "System.hpp"

namespace Client {

    namespace Components {

        class ComponentManager {
            public:
                ComponentManager();
                ~ComponentManager();

                Component &CreateComponent(Component &c);

                std::map<Component, std::vector<Systems::System>> _components;
        };

    }

}

#endif /* !COMPONENTMANAGER_HPP_ */

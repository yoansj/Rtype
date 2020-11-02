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
#include <memory>

#include "SystemManager.hpp"
#include "Component.hpp"
#include "System.hpp"

namespace Client {

    namespace Components {

        /**
         * @brief Handles all Components of the ECS, is a singleton
         * Use Get() to access the instance
         * */
        class ComponentManager {
            public:
                /**
                 * @brief Allow access to the ComponentManager class
                 * @return ComponentManager instance
                 */
                static ComponentManager &Get() {static ComponentManager comp; return (comp);};

                /**
                 * @brief Creates a component and adds-it to the component list
                 * @note No note
                 * @param  &c: Reference to the component that was created
                 * @return The component created
                 */
                Component const &CreateComponent(Component const &c);

            private:
                std::map<std::shared_ptr<Component>, std::vector<std::shared_ptr<Systems::System>>> _components;

                ComponentManager() {};
                ~ComponentManager() = default;
                ComponentManager &operator= (const ComponentManager&) = delete;
                ComponentManager (const ComponentManager&) = delete;
        };

    }

}

#endif /* !COMPONENTMANAGER_HPP_ */

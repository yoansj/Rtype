/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include "System.hpp"
#include "Component.hpp"

#include <map>
#include <string>
#include <memory>

namespace Client {

    namespace Systems {

        /**
         * @brief Factory pour les systèmes
         */
        class SystemManager {
            public:
                static SystemManager &Get() {static SystemManager sys; return (sys);};
                void CreateSystem(std::shared_ptr<System> s);
                std::shared_ptr<System> &GetSystem(std::string name);
                void AddComponentToSystem(std::string systemName, std::shared_ptr<Components::Component> c);
                void Update();

            private:
                SystemManager();
                ~SystemManager() = default;
                SystemManager &operator= (const SystemManager&) = delete;
                SystemManager (const SystemManager&) = delete;

                std::map<std::string, std::shared_ptr<System>> _systems;
        };

    }

}

#endif /* !SYSTEMMANAGER_HPP_ */

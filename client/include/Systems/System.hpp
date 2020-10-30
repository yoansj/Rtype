/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Component.hpp"

#include <string>
#include <vector>
#include <memory>

namespace Client {

    namespace Systems {

        /**
         * @brief  Classe abstraite dont tous les systèmes héritent
         * @note Ne pas instancier vu que c'est une classe abstraite
         * @retval None
         */
        class System {
            public:
                System(std::string name) : _name(name) {};
                std::string GetName() const {return (_name);};
                void AddComponent(std::shared_ptr<Components::Component> c) {_components.push_back(c);};
                ~System() {};
                virtual void Init() {};
                virtual void Update() {};

            private:
                std::string _name;
                std::vector<std::shared_ptr<Components::Component>> _components;
        };

    }

}
#endif /* !SYSTEM_HPP_ */

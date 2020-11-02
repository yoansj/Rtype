/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
#define POSITIONSYSTEM_HPP_

#include "System.hpp"
#include "PositionComponent.hpp"

#include <iostream>

namespace Client {

    namespace Systems {

        /**
         * @brief  Classe abstraite dont tous les systèmes héritent
         * @note Ne pas instancier vu que c'est une classe abstraite
         * @retval None
         */
        class PositionSystem : public System {
            public:
                PositionSystem() : System("PositionSystem") {};
                ~PositionSystem() {};
                void Init() override {};
                void Update() override {
                    for (int i = 0; i != _components.size(); i++) {
                        std::cout << "Position " << i << ": ";
                        if (_components[i]._name == "Position") {
                            dynamic_cast<Client::Components::PositionComponent&>(_components[i]).print();
                        }
                    }
                };
        };

    }

}

#endif /* !POSITIONSYSTEM_HPP_ */

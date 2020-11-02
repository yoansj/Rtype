/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "ComponentManager.hpp"

namespace Engine {

    /**
     * @brief This class represents the Systems of our engine
     * Each system has its own component type and contain a vector of components
     * The systems that inherit this class must implement the update function
     */
    template<class AbstractComponent>
    class System {
        public:
            System() = default;
            ~System() = default;

            AbstractComponent &create(Entity e) {
                return (_components.create(e));
            }

            bool destroy(Entity e) {
                return (_components.destroy(e));
            }

            AbstractComponent &getComponent(Entity e) {
                return (_components.getComponent(e));
            }

            size_t size() {
                return (_components.size());
            }

            virtual void update() {
                //Each system should implement this function
                //Even if it does nothing
            };

            const AbstractComponent &operator[](std::size_t size) {
                return (_components[size]);
            }

        protected:
            ComponentManager<AbstractComponent> _components;
    };

}
#endif /* !SYSTEM_HPP_ */

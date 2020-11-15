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
     * This class represents the Systems of our engine
     * Each system has its own component type and contain a vector of components
     * The systems that inherit this class must implement the update function
     */
    template<class AbstractComponent>
    class System {
        public:
            System() = default;
            ~System() = default;

            /**
             * Create a entity.
             * @param params1 Entity e
             * @return value AbstractComponent &
             */
            AbstractComponent &create(Entity e) {
                return (_components.create(e));
            }

            /**
             * Destroy a entity.
             * @param params1 Entity e
             * @return value bool
             */
            bool destroy(Entity e) {
                return (_components.destroy(e));
            }

            /**
             * Get component entity
             * @param params1 Entity e
             * @return value AbstractComponent &
             */
            AbstractComponent &getComponent(Entity e) {
                return (_components.getComponent(e));
            }

            /**
             * Get all component entity.
             * @return value size_t
             */
            size_t size() {
                return (_components.size());
            }

            /**
             * Update every function implement in system.
             */
            virtual void update() {
                //Each system should implement this function
                //Even if it does nothing
            }

            /**
             * Get all components.
             * @return value std::vector<AbstractComponent>
             */
            std::vector<AbstractComponent> &getComponents() {
                return (_components.getComponents());
            }


            /**
             * @brief Check if a component exist.
             * @param params1 Entity e
             * @return value bool
             */
            bool Exist(Entity e) {
                return (_components.Exist(e));
            }
        protected:
            ComponentManager<AbstractComponent> _components;
    };

}
#endif /* !SYSTEM_HPP_ */

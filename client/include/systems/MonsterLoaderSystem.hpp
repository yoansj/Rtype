/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** LibLoaderSystem
*/

#ifndef LIBLOADERSYSTEM_HPP_
#define LIBLOADERSYSTEM_HPP_

#include "System.hpp"
#include "Position.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>
#include <dlfcn.h>
#include <memory>

namespace Engine {
    /**
     * @brief Monster Loader Error for managing error.
     * 
     */
    class MonsterLoaderError : public std::exception {
        public:
            /**
             * @brief Construct a new Monster Loader Error object
             * 
             * @param std::string const &message 
             */
            MonsterLoaderError(std::string const &message) :
            _message(message) {};

            /**
             * @brief Return message error from what()
             * 
             * @return char const* 
             */
            char const *what() const noexcept override { return _message.data();};

        private:
            std::string _message;
    };

    /**
     * @brief Monster load manager from a library
     */
    class MonsterLoaderSystem  {
        public:
            MonsterLoaderSystem() {};
            ~MonsterLoaderSystem() = default;

            /**
             * @brief Load a monster from libraries
             * 
             * @param std::vector<std::string> _libs 
             */
            void load(std::vector<std::string> _libs);

            /**
             * @brief Get the Factory for Monster
             * 
             * @param int index 
             * @return void* 
             */
            void *getFactory(int index) { return (_monstersFactories[index]); };

        private:
            std::vector<void *> _monstersLib;
            std::vector<void *> _monstersFactories;
    };

}

#endif /* !LIBLOADERSYSTEM_HPP_ */

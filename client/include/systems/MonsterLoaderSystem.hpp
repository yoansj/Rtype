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

    class MonsterLoaderError : public std::exception {
        public:
            MonsterLoaderError(std::string const &message) :
            _message(message) {};

            char const *what() const noexcept override { return _message.data();};

        private:
            std::string _message;
    };

    /**
     * @brief  Position system used on the Position component
     */
    class MonsterLoaderSystem  {
        public:
            MonsterLoaderSystem() {};
            ~MonsterLoaderSystem() = default;

            void load(std::vector<std::string> _libs);

            void *getFactory(int index) { return (_monstersFactories[index]); };

        private:
            std::vector<void *> _monstersLib;
            std::vector<void *> _monstersFactories;
    };

}

#endif /* !LIBLOADERSYSTEM_HPP_ */

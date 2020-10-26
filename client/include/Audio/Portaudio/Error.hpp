/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Error
*/

#ifndef PORTAUDIOERROR_HPP_
#define PORTAUDIOERROR_HPP_

#include <iostream>
#include <exception>

namespace Babel {
    namespace Audio {
        class PortaudioError : public std::exception {
            public:
                PortaudioError(std::string const &message) :
                    _message(message), _type("Portaudio Error") { };

                std::string const &getType() const { return _type; };
                char const *what() const noexcept override { return _message.data(); };

            private:
                std::string _message;
                std::string _type;
        };
    }
}

#endif /* !PORTAUDIOERROR_HPP_ */

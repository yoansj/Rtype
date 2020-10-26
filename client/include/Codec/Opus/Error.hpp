/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** OpusError
*/

#ifndef OPUSERROR_HPP_
#define OPUSERROR_HPP_

#include <iostream>
#include <exception>

namespace Babel {
    namespace Codec {
        class OpusError : public std::exception {
            public:
                OpusError(std::string const &message) :
                    _message(message), _type("Opus Error") { };

                std::string const &getType() const { return _type; };
                char const *what() const noexcept override { return _message.data(); };

            private:
                std::string _message;
                std::string _type;
        };
    }
}

#endif /* !OPUSERROR_HPP_ */

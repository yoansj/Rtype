/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <iostream>

namespace Babel {
    namespace Json {
        class ParserError : public std::exception {
            public:
                ParserError(std::string const &message) :
                    _message(message), _type("Parser Error") { };

                std::string const &getType() const { return _type; };
                char const *what() const noexcept override { return _message.data(); };

            private:
                std::string _message;
                std::string _type;
        };
    }
}

#endif /* !ERROR_HPP_ */

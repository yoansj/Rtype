/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Error
*/

#ifndef NETWORKERROR_HPP_
#define NETWORKERROR_HPP_

#include <exception>
#include <iostream>

namespace Babel {
    namespace Network {
        class NetworkError : public std::exception {
            public:
                NetworkError(std::string const &message) :
                    _message(message), _type("Network Error") { };

                std::string const &getType() const { return _type; };
                char const *what() const noexcept override { return _message.data(); };

            private:
                std::string _message;
                std::string _type;
        };
    }
}

#endif /* !NETWORKERROR_HPP_ */

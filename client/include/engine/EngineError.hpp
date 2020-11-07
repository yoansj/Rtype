/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** EngineError
*/

#ifndef ENGINEERROR_HPP_
#define ENGINEERROR_HPP_

#include <string>
#include <exception>

class EngineError : public std::exception {
    public:
        EngineError(std::string const &type, std::string const &message) :
        _message(message), _type(type) {};

        char const *what() const noexcept override { return _message.data();};
        std::string getType() const{ return _type;};

    private:
        std::string _message;
        std::string _type;
};

#endif /* !ENGINEERROR_HPP_ */

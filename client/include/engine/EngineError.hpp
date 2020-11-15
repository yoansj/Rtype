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

/**
 * @brief Game Engine managing error.
 * 
 */
class EngineError : public std::exception {
    public:
        /**
         * @brief Construct a new Engine Error object
         * 
         * @param std::string const &type
         * @param std::string const &message 
         */
        EngineError(std::string const &type, std::string const &message) :
        _message(message), _type(type) {};

        /**
         * @brief Return message error from what()
         * 
         * @return char const* 
         */
        char const *what() const noexcept override { return _message.data();};

        /**
         * @brief Get the Type object
         * 
         * @return std::string 
         */
        std::string getType() const{ return _type;};

    private:
        std::string _message;
        std::string _type;
};

#endif /* !ENGINEERROR_HPP_ */

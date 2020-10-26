/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Conversion
*/

#ifndef CONVERSION_HPP_
#define CONVERSION_HPP_

#include <type_traits>
#include <algorithm>
#include <iostream>
#include <vector>
#include <QDebug>

namespace Babel {
    /*
    ** DO NOT USE THIS FUNCTION PLEASE !!!
    */
    template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    static std::string numericalToBytes(T const &nb)
    {
        std::string bytes(sizeof(T), ' ');
        // std::vector<char> bytes(sizeof(T));

        std::copy(
            reinterpret_cast<const char *>(&nb),
            reinterpret_cast<const char *>(&nb) + sizeof(T),
            bytes.data()
        );
        return (bytes);
    }

    template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    static T bytesToNumerical(const char *bytes)
    {
        T nb;

        std::copy(bytes, bytes + sizeof(T), reinterpret_cast<char *>(&nb));
        return (nb);
    }

    template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    static T bytesToNumerical(std::string const &str)
    { return bytesToNumerical<T>(str.data()); }
}

#endif /* !CONVERSION_HPP_ */

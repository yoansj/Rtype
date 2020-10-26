/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** String
*/

#ifndef STRING_HPP_
#define STRING_HPP_

#include <iostream>
#include <vector>
#include <numeric>

namespace Babel {
    static std::vector<std::string> const _split(std::string str, std::string const &del)
    {
        std::size_t pos = 0;
        std::vector<std::string> v;

        while((pos = str.find(del)) != std::string::npos) {
            v.push_back(str.substr(0, pos));
            str.erase(0, pos + del.length());
        }
        v.push_back(str);
        return (v);
    };

    static std::string const _join(std::vector<std::string> const &v, std::string const &del = " ")
    {
        std::string str;

        for (auto const &e : v) str += e + del;
        return (str.substr(0, str.length() - del.length()));
    };

    static std::size_t _find_first_of(std::string const &str, std::string const &strToFind, std::size_t const &pos = 0)
    {
        std::size_t i = 0;

        for (; i + pos < str.length(); ++i)
            if (strToFind.find(str[i + pos]) != std::string::npos)
                return (i);
        return (std::string::npos);
    };
}

#endif /* !STRING_HPP_ */

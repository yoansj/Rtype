/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** VariadicTypeTraits
*/

#ifndef VARIADICTYPETRAITS_HPP_
#define VARIADICTYPETRAITS_HPP_

#include <typeinfo>

namespace Babel {
    template<class T, class ...>
    struct are_same : std::true_type { };

    template<class T, class Next, class ...List>
    struct are_same<T, Next, List...>
        : std::integral_constant<
            bool,
            std::is_same<T, Next>::value && are_same<T, List...>{ }
        >
    { };

    template<class T, class ...>
    struct are_base_of : std::true_type { };

    template<class T, class Next, class ...List>
    struct are_base_of<T, Next, List...>
        : std::integral_constant<
            bool,
            std::is_base_of<T, Next>::value && are_base_of<T, List...>{ }
        >
    { };
}

#endif /* !VARIADICTYPETRAITS_HPP_ */

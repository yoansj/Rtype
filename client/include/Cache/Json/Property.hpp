/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Property
*/

#ifndef PROPERTY_HPP_
#define PROPERTY_HPP_

#include <iostream>
#include <memory>

namespace Babel {
    namespace Json {
        enum Type {
            _none = -1,
            _int = 0,
            _double,
            _string,
            _array,
            _object
        };

        class Object;

        class Property {
            public:
                Property(std::string const &name, Type type, Type subType = Type::_none) :
                    _name(name), _type(type), _subType(type == Type::_array ? subType : Type::_none) { };
                ~Property() = default;

                std::string const &getName() const { return _name; };
                Type getType() const { return _type; };

                virtual void dump(std::size_t = 0, std::size_t = 4) const = 0;
                virtual void print(std::size_t = 0, std::size_t = 4) const = 0;

                virtual Property const &operator=(int const &) { return *this; };
                virtual Property const &operator=(double const &) { return *this; };
                virtual Property const &operator=(std::string const &) { return *this; };
                virtual Property const &operator=(std::shared_ptr<Property> const &) { return *this; };

                virtual Property const &operator=(std::vector<int> const &newData) { return (*this); };
                virtual Property const &operator=(std::vector<double> const &newData) { return (*this); };
                virtual Property const &operator=(std::vector<std::string> const &newData) { return (*this); };
                virtual Property const &operator=(std::vector<std::shared_ptr<Object>> const &newData) { return (*this); };

            protected:
                std::string _name;
                Type _type;
                Type _subType;
        };
    }
}

#endif /* !PROPERTY_HPP_ */

/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Value
*/

#ifndef VALUE_HPP_
#define VALUE_HPP_

#include "String.hpp"
#include "Property.hpp"

namespace Babel {
    namespace Json {
        template <class T, bool B = std::is_same<int, T>::value || std::is_same<double, T>::value || std::is_same<std::string, T>::value>
        class Value;

        template <class T>
        class Value<T, true> : public Property {
            public:
                Value(std::string const &name, int const &data) : Property(name, Type::_int), _data(data) { };
                Value(std::string const &name, double const &data) : Property(name, Type::_double), _data(data) { };
                Value(std::string const &name, std::string const &data) : Property(name, Type::_string), _data(data) { };
                ~Value() = default;

                T const &getData() const { return _data; };
                void setData(T const &data) { _data = data; }

                void dump(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    std::cout << std::string(base_indent, ' ')
                        << "Type: " << _type << " | name: " << _name << " | value: " << _data << std::endl;
                }
                void print(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    auto data = getType() == Type::_string ? '"' + _data + '"' : _data;
                    std::cout << std::string(base_indent, ' ')
                        << "\"" << _name << "\": "
                        << data << std::endl;
                }

                Property const &operator=(T const &newData) override { setData(newData); return (*this); };

            private:
                T _data;
        };

        template <class T>
        static std::shared_ptr<Value<T>> createValue(std::string const &name, T const &data)
        {
            return (std::make_shared<Value<T>>(name, data));
        }

        // template <class T>
        // std::shared_ptr<Property> copyProperty(std::shared_ptr<Property> const &prop)
        // {
        //     auto ptr;
        //     if (ptr = std::dynamic_pointer_cast<Value<T>>(prop)) {
        //         return (createValue(ptr->getName(), ptr->getData()));
        //     } else if (ptr = std::dynamic_pointer_cast<Object>(prop)) {

        //     }
        // }
    }
}

#endif /* !VALUE_HPP_ */

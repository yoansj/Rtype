#ifndef BSON_VALUE_HPP
#define BSON_VALUE_HPP

#include <iostream>
#include <vector>
#include <typeindex>

namespace Packet {
    class A_Bson_Value
    {
        public:
            virtual ~A_Bson_Value() = default;

            virtual std::type_index get_type() = 0;
            
            // template<T>
            // virtual T getValue() = 0;
            // T getValue() = 0;
            // bool setValue(const T &val) = 0;

    };

    template<class T = size_t>
    class Bson_Value: public A_Bson_Value
    {
        private:
            T value;
        public:
            Bson_Value(const T &val) {
                value = val;
            }
            // Bson_Value(const std::vector<std::string> &vect);
            // Bson_Value(const std::string &str);
            // Bson_Value(const size_t &val);
    
            Bson_Value(const Bson_Value<T> &cpy)
            {
                value = cpy.value;
            }

            T get_value() {
                return value;
            }
            bool set_value(const T &val);
            std::type_index get_type() {
                return typeid(value);
            }
    };
};

#endif

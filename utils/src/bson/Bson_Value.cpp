#include "Bson_Value.hpp"

namespace Packet {

    template<class T>
    bool Bson_Value<T>::set_value(const T &val) {
        value = val;
        return true;
    }
};
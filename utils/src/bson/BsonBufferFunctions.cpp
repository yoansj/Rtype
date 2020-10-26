#include "Bson.hpp"

void Packet::Bson::add_value(const size_t &value)
{
    const void *a = static_cast<const void *>(&value);
    const unsigned char *a2 = static_cast<const unsigned char *>(a);
    int i = 0;
    auto aim = Packet::Var_size::INT_64_S;

    //check endianess of windows
    while (i < aim) {
        this->buffer += a2[i++];
    }
    total_length += aim;
}

void Packet::Bson::add_value(const std::vector<std::string> &values)
{
    size_t size = 0;

    for (auto &val: values) {
        size = val.size();
        add_value(size);
        buffer += val;
        total_length += size;
    }
}

void Packet::Bson::add_value(const std::string &value)
{
    buffer += value;
    total_length += value.size();
}

void Packet::Bson::add_key(const std::string &key)
{
    buffer += key;
    buffer += '\0';
    total_length += key.size() + 1;
    _keys.push_back(key);
}

void Packet::Bson::add_type(const enum Packet::Type &type)
{
    const void *a = static_cast<const void *>(&type);
    const unsigned char *a2 = static_cast<const unsigned char *>(a);
    int i = 0;
    auto aim = Packet::Var_size::INT_64_S;

    while (i < aim) {
        if (i >= sizeof(type))
            this->buffer += '\0';
        else
            this->buffer += a2[i];
        i++;
    }
    total_length += Packet::Var_size::INT_64_S;
}

void Packet::Bson::add_field(const std::string &key, const size_t &value)
{
    add_type(Packet::Type::INT_64);

    add_key(key);

    add_value(value);
}

void Packet::Bson::add_field(const std::string &key, const std::vector<std::string> &values)
{
    add_type(Packet::Type::VECTOR_STR);
    size_t nb_of_element = values.size();

    // for (auto val: values) {
        // allsize += val.size() + Packet::Var_size::INT_64_S; //concat size + value
    // }

    add_value(nb_of_element);

    add_key(key);

    add_value(values);
}

void Packet::Bson::add_field(const std::string &key, const std::string &value)
{
    add_type(Packet::Type::STRING);
    add_value(value.size());
    add_key(key);
    add_value(value);
}

void Packet::Bson::add_field(const std::string &key, const Bson &value)
{
    add_type(Packet::Type::BSON_OBJ);
    add_key(key);
    add_value(value.serialize());
}

void Packet::Bson::add_field(const std::string &key, const std::vector<Bson> &values)
{
    add_type(Packet::Type::VECTOR_BSON);
    size_t nb_of_element = values.size();

    add_value(nb_of_element);
    add_key(key);

    for (size_t i = 0; i < nb_of_element; i++) {
        add_value(values[i].serialize());
    }
}
#include "Bson.hpp"

Packet::Bson::Bson(): constructed_from_buff(false)
{
    
}

Packet::Bson::Bson(const std::string &_buffer): constructed_from_buff(true), buffer(_buffer)
{
    Bson::iterator it(buffer);
    total_length = it->entire_buffer_len;
    while (1) {
        _keys.push_back(it->key);
        if (it.end())
            break;
        ++it;
    }
}

Packet::Bson::Bson(const Bson &cpy)
{
    this->total_length = cpy.total_length;
    this->_keys = cpy._keys;
    this->buffer = cpy.serialize();
    this->constructed_from_buff = true;
}


const std::string Packet::Bson::serialize(void) const
{
    if (constructed_from_buff)
        return buffer;
    else {
        std::string new_buff;

        size_t len = total_length + 8; //overall size
        const void *a = static_cast<const void *>(&len);
        const unsigned char *a2 = static_cast<const unsigned char *>(a);
        int i = 0;
        auto aim = Packet::Var_size::INT_64_S;

        //check endianess of windows
        while (i < aim) {
            new_buff += a2[i++];
        }
        new_buff += buffer;
        return new_buff;
    }
}

const std::vector<std::string> Packet::Bson::get_keys(void)
{
    return _keys;
}

bool Packet::Bson::keyExist(const std::string &_key)
{
    for (auto &key : _keys) {
        if (key == _key)
            return true;
    }
    return false;
}

Packet::Bson::iterator Packet::Bson::begin()
const
{
    Packet::Bson::iterator it(this->serialize());

    return it;
}


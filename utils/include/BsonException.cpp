#include "BsonException.hpp"

Packet::BsonException::BsonException(const std::string &str_error)
{
    std::stringstream s1;

    s1 << "Bson Exception: " << str_error << std::endl;
    _str_error = s1.str();
}


const char *Packet::BsonException::what()
const noexcept
{
    return _str_error.c_str();
}

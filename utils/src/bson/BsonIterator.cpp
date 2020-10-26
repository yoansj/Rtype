#include "Bson.hpp"
#include "BsonException.hpp"

namespace Packet {
    Bson::iterator::iterator(const std::string &buff): 
    type(Type::UNKNOWN), _current_index(0), buffer(buff), entire_buffer_len(0)
    {
        get_total_size();
        jump_to_next_field();
    }

    Bson::iterator::iterator(const iterator &cpy)
    {
        _current_index = cpy._current_index;
        buffer = cpy.buffer;
        _value = cpy._value;
        entire_buffer_len = cpy.entire_buffer_len;
        key = cpy.key;
        type = cpy.type;
    }

    const Bson::iterator *Bson::iterator::operator->() const
    {
        return this;
    }

    void Bson::iterator::get_total_size()
    {
        if (buffer.size() < Var_size::INT_64_S) {
            throw BsonException("Buffer is too small to read the overall size");
        }
        void *v = static_cast<void *>(&entire_buffer_len);
        unsigned char *buff = static_cast<unsigned char *>(v);
        int i = 0;
 
        //carefull with endianess
        while (i < Var_size::INT_64_S) {
            buff[i] = buffer[_current_index++];
            i++;
        }
        if (buffer.size() < entire_buffer_len)
            throw BsonException("The current buffer size is smaller than the specified overall size");

    }


    void Bson::iterator::get_value(size_t &value)
    {
        void *v = static_cast<void *>(&value);
        unsigned char *buff = static_cast<unsigned char *>(v);
        int i = 0;

        if (_current_index + Var_size::INT_64_S > entire_buffer_len)
            throw BsonException("Something went wrong during buffer parsing at " + std::to_string(_current_index) + " byte");
        
        //carefull with endianess
        while (i < Var_size::INT_64_S) {
            buff[i] = buffer[_current_index++];
            i++;
        }
    }

    std::string Bson::iterator::get_key()
    {
        std::string value;
        
        while (buffer[_current_index]) {
            value += buffer[_current_index++];
            if (_current_index > entire_buffer_len)
                throw BsonException("Something went wrong during buffer parsing at " + std::to_string(_current_index) + " byte");
        }
        return value;
    }

    void Bson::iterator::get_value(std::string &value, size_t size)
    {
        int i = 0;
    
        if (_current_index + size > entire_buffer_len)
            throw BsonException("Something went wrong during buffer parsing at " + std::to_string(_current_index) + " byte");
        while (i < size) {
            value += buffer[_current_index++];
            i++;
        }
    }

    void Bson::iterator::get_value(std::vector<std::string> &values, size_t nb_elements)
    {
        std::string value = "";
        size_t str_len = 0;
        while (nb_elements--) {
            value = "";
            str_len = 0;
            get_value(str_len);
            get_value(value, str_len);
            values.push_back(value);
        }
    }

    void Bson::iterator::get_value(Bson &value)
    {
        std::string rest;
        size_t size = 0;
        get_value(size);
        get_value(rest, (size - 8));

        std::string buffer = Bson::turn_into_byte_string<size_t>(size);
        buffer += rest;
        value = Bson(buffer);
    }

    Type Bson::iterator::get_type()
    {
        size_t type = 0;

        if (_current_index + Var_size::INT_64_S > entire_buffer_len)
            throw BsonException("Something went wrong during buffer parsing at " + std::to_string(_current_index) + " byte");
        get_value(type);
        if (type == Type::BSON_OBJ || type == Type::VECTOR_STR 
            || type == Type::STRING || type == Type::INT_64 
            || type == Type::BSON_OBJ || type == Type::VECTOR_BSON) {
            return static_cast<Type>(type);
        }
        return Type::UNKNOWN;
    }

    void Bson::iterator::get_field_string(void)
    {
        size_t size = 0;

        get_value(size);
        key = get_key();
        _current_index++; //skip trailling 0
        std::string str;
        get_value(str, size);
        swap_ptr<std::string>(str);
    }

    void Bson::iterator::get_field_int64(void)
    {
        size_t value = 0;
    
        key = get_key();        
        _current_index++; //skip trailling 0
        get_value(value);
        swap_ptr<size_t>(value);
    }

    void Bson::iterator::get_field_bson(void)
    {
        Bson value;
        key = get_key();
        _current_index++; //skip trailling 0
        get_value(value);
        swap_ptr<Bson>(value);
    }

    void Bson::iterator::get_field_vector_bson(void)
    {
        std::vector<Bson> arr;

        size_t nb_of_elements;

        get_value(nb_of_elements);
        key = get_key();
        _current_index++; //skip trailling 0
        
        Bson tmp;
        for (int i = 0; i < nb_of_elements; i++) {
            get_value(tmp);
            arr.push_back(tmp);
        }
        
        // get_value(arr, nb_elements);
        swap_ptr<std::vector<Bson>>(arr);
    }

    void Bson::iterator::get_field_vector_str(void)
    {
        std::vector<std::string> arr;

        size_t nb_elements;

        get_value(nb_elements);
        key = get_key();
        _current_index++; //skip trailling 0
        get_value(arr, nb_elements);
        swap_ptr<std::vector<std::string>>(arr);
    }

    bool Bson::iterator::end()
    {
        return _current_index == entire_buffer_len;
    }

    void Bson::iterator::jump_to_next_field()
    {
        if (!this->end()) {
            Type _type = get_type();
            type = _type;

            if (type == Type::UNKNOWN)
                throw BsonException("parse an unknown type at " + std::to_string(_current_index - 8) + " byte"); 
            if (type == Type::STRING) {
                get_field_string();
            }
            if (type == Type::INT_64) {
                get_field_int64();
            }
            if (type == Type::VECTOR_STR) {
                get_field_vector_str();
            }
            if (type == Type::VECTOR_BSON) {
                get_field_vector_bson();
            }
            if (type == Type::BSON_OBJ) {
                get_field_bson();
            }
         }
    }

    Bson::iterator& Bson::iterator::operator++()
    {
        jump_to_next_field();
        return *this;
    }


};
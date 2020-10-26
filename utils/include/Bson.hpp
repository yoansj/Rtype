#ifndef BSON_HPP
#define BSON_HPP

#include "BsonException.hpp"
#include "Bson_Value.hpp"
#include <iostream>
#include <vector>
#include <memory>

namespace Packet {
    enum Type {
        BSON_OBJ = 0x01,
        VECTOR_BSON = 0x02, 
        VECTOR_STR = 0x04, 
        STRING = 0x08,
        INT_64 = 0x10,
        UNKNOWN = 0x20 //NULL value or unknown
    };
    
    enum Var_size  { //in bytes: to ensure cross compatibility with windows
        INT_64_S = sizeof(size_t),
        BYTE_STRING_S = sizeof(char)
    };

    class Bson {
        class iterator;
        public:
            explicit Bson();
            explicit Bson(const std::string &buffer);
            Bson(const Bson &cpy);
            template<typename ...Args>
            explicit Bson(Args ...args) : total_length(0), constructed_from_buff(false){
                this->insert(args...);
            }
            ~Bson() = default;

            template<typename T>
            static std::string turn_into_byte_string(T val)
            {
                void *v = static_cast<void *>(&val);
                unsigned char *buff = static_cast<unsigned char *>(v);
                size_t size = sizeof(T);
                std::string buffer;
                
                //carefull bigendian
                for (size_t i = 0; i < size; i++)
                    buffer += buff[i];
                return buffer;
            }

            const std::string serialize(void) const;

            bool insert() {
                return true;
            }

            template<typename ...Args>
            bool insert(const std::string &key, const std::string &value, Args ...args) {
                if (keyExist(key)) {
                    throw BsonException("cannot insert \"" + key + "\", key already exist");
                }
                size_t size = key.size();
                add_field(key, value);
                return insert(args...);
            }

            template<typename ...Args>
            bool insert(const std::string &key, const std::vector<std::string> &values, Args ...args) {
                if (keyExist(key)) {
                    throw BsonException("cannot insert \"" + key + "\", key already exist");
                }
                add_field(key, values);
                return insert(args...);
            }

            template<typename ...Args>
            bool insert(const std::string &key, const size_t &value, Args ...args) {
                if (keyExist(key)) {
                    throw BsonException("cannot insert \"" + key + "\", key already exist");
                }
                add_field(key, value);
                return insert(args...);
            }
            template<typename ...Args>
            bool insert(const std::string &key, const std::vector<Bson> &values, Args ...args) {
                if (keyExist(key)) {
                    throw BsonException("cannot insert \"" + key + "\", key already exist");
                }
                add_field(key, values);
                return insert(args...);
            }

            template<typename ...Args>
            bool insert(const std::string &key, const Packet::Bson &value, Args ...args) {
                if (keyExist(key)) {
                    throw BsonException("cannot insert \"" + key + "\", key already exist");
                }
                add_field(key, value);
                return insert(args...);
            }

            template<typename T>
            T find(const std::string &key) const {
                if (!_keys.size()) {
                    throw BsonException("can't find any key within this bson");
                }

                auto it = begin();
                while (1) {
                    // std::cout << it->key << std::endl;
                    if (key == it->key) {
                        return it.get<T>();
                    }
                    if (it.end())
                        break;
                    ++it;
                }
                throw BsonException("fail to find key");
            }



            enum Type get_type(const std::string &key);
            const std::vector<std::string> get_keys(void);

        private:
            Packet::Bson::iterator begin() const;
            bool constructed_from_buff;
            bool keyExist(const std::string &key);

            //buffer method
            void add_value(const size_t &value);
            void add_value(const std::vector<std::string> &values);
            void add_value(const std::string &value);
            void add_key(const std::string &key);
            
            void add_type(const enum Packet::Type &type);
            
            void add_field(const std::string &key, const size_t &value);
            void add_field(const std::string &key, const std::vector<std::string> &values);
            void add_field(const std::string &key, const std::string &value);

            void add_field(const std::string &key, const Bson &value);
            void add_field(const std::string &key, const std::vector<Bson> &value);

            
        private:
            size_t total_length;
            std::vector<std::string> _keys;
            std::string buffer;
        
        //bson iterator
        class iterator {
            public:
                size_t entire_buffer_len;
                std::string key;
                enum Type type;
            public:
                iterator(const std::string &buff);
                iterator(const iterator &cpy);
                iterator(const std::string &buff, const std::string &key);       
                // operator++
                //operator->key
                // get_value()
                template<typename T>
                T get() {
                    if (_value->get_type() != typeid(T))
                        throw BsonException("Error during get iterator method, the type specified doesn't match");
                    if (type == Type::UNKNOWN)
                        throw BsonException("There is no type inside this iterator");
                    std::shared_ptr<Bson_Value<T>> new_ptr = std::dynamic_pointer_cast<Bson_Value<T>> (_value);
                    if (new_ptr == nullptr)
                        throw BsonException("Dynamic pointer cast has failed: cannot retrieve the value from this iterator");
                    return new_ptr->get_value();
                }

                const iterator *operator->() const;
                
                iterator& operator++();

                bool end();

            private:
                Type get_type();
                std::string get_key();
                void get_total_size();

                void get_value(size_t &value);
                void get_value(std::string &value, size_t size);
                void get_value(std::vector<std::string> &values, size_t nb_elements);
                void get_value(Bson &value);
                
                void get_field_string(void);
                void get_field_int64(void);
                void get_field_vector_str(void);
                void get_field_vector_bson(void);
                void get_field_bson(void);

                void jump_to_next_field();

                template<typename T>
                void swap_ptr(const T &val) {
                    std::shared_ptr<Bson_Value<T>> tmp(new Bson_Value<T>(val));
                    _value = tmp;
                }
            private:
                size_t _current_index;
                
                std::string buffer;
                std::shared_ptr<A_Bson_Value> _value;
        };
        

    };

    const std::string build_message(int message_code, const Bson &obj);
    const std::string build_message(int message_code);
};

#endif

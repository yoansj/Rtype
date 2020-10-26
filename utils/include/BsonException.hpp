//fail to getkey
//key already exist

#ifndef BSON_EXCEPTION
#define BSON_EXCEPTION

#include <sstream>

namespace Packet {

    class BsonException : public std::exception {
        
        public:
            // BsonException(const std::string &str_error, const std::string &componentName = "Default server error");
            BsonException(const std::string &str_error);
            const char *what() const noexcept override;

        protected:
            std::string _str_error;
    };
};

#endif
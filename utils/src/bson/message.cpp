#include "Bson.hpp"

namespace Packet {
    const std::string build_message(int message_code, const Bson &obj)
    {
        const void *a = static_cast<const void *>(&message_code);
        const unsigned char *a2 = static_cast<const unsigned char *>(a);
        int i = 0;
        std::string message;

        //check endianess of windows
        while (i < sizeof(int)) {
            message += a2[i];
            i++;
        }
        message += obj.serialize();
        return message;
    }

    const std::string build_message(int message_code)
    {
        std::string message = Packet::Bson::turn_into_byte_string(message_code);

        return message;
    }

};
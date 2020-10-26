/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** data
*/

#ifndef O_DATA_H_
#define O_DATA_H_

#include <opus/opus.h>

#define O_SAMPLE_RATE (48000)           // Sample Rate in Hz
#define O_FPB (960)                     // Frame Per Buffer
#define O_NB_CHANNEL (2)                // 2 Channels : stereo
#define O_APP (OPUS_APPLICATION_VOIP)   // Default Application mode
#define O_DATA_SIZE (4000)              // Default max data size in bytes

namespace Babel {
    namespace Codec {
        using Packet = std::vector<unsigned char>;
        using PCM = std::vector<float>;
    }
}

#endif /* !O_DATA_H_ */

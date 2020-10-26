/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** AudioManager
*/

#ifndef AUDIOMANAGER_HPP_
#define AUDIOMANAGER_HPP_

#include "Portaudio.hpp"
#include "Encoder.hpp"
#include "Decoder.hpp"

namespace Babel {
    namespace Audio {
        class AudioManager {
            public:
                AudioManager() = default;
                ~AudioManager() = default;

                void init()
                {
                    _audio.closeAllStreams();
                    _audio.openIStream(0, true);
                    _audio.openOStream(1, true);
                }

                void close()
                { _audio.closeAllStreams(); }

                std::vector<Codec::Packet> getEncodedInput()
                { return (_encoder(_audio.getPCMs(0))); }

                void setDecodedOutput(std::vector<Codec::Packet> const &packetsList)
                { _audio.setPCMs(1, _decoder(packetsList)); }

            private:
                Portaudio _audio;
                Codec::Encoder _encoder;
                Codec::Decoder _decoder;
        };
    }
}

#endif /* !AUDIOMANAGER_HPP_ */

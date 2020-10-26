/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Decoder
*/

#ifndef DECODER_HPP_
#define DECODER_HPP_

#include <opus/opus.h>

#include "IDecoder.hpp"
#include "Error.hpp"
#include "data.h"

namespace Babel {
    namespace Codec {
        class Decoder : public IDecoder {
            public:
                Decoder() :
                    _error(0),
                    _state(opus_decoder_create(O_SAMPLE_RATE, O_NB_CHANNEL, &_error))
                { checkError(); };
                ~Decoder()
                { opus_decoder_destroy(_state); }

                void checkError() const override
                {
                    if (_error < 0)
                        throw OpusError("Opus Error has occured. Error number: " + std::to_string(_error));
                }

                PCM decode(Packet const &packet) override
                {
                    PCM decoded(O_FPB * 2);
                    unsigned long nb = opus_decode_float(_state, packet.data(), packet.size(), decoded.data(), O_FPB, 0);

                    if (nb < 0)
                        throw OpusError("Error when decoding: " + std::to_string(nb));
                    return (decoded);
                }

                std::vector<PCM> decodeList(std::vector<Packet> const &packets) override
                {
                    std::vector<PCM> pcms(packets.size());

                    for (std::size_t i = 0; i < packets.size(); ++i)
                        pcms[i] = (*this)(packets[i]);
                    return (pcms);
                }

                PCM operator()(Packet const &packet) override
                { return (decode(packet)); }

                std::vector<PCM> operator()(std::vector<Packet> const &packets) override
                { return (decodeList(packets)); }

            private:
                int _error;
                OpusDecoder *_state;
        };
    }
}

#endif /* !DECODER_HPP_ */

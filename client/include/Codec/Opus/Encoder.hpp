/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Encoder
*/

#ifndef ENCODER_HPP_
#define ENCODER_HPP_

#include <opus/opus.h>

#include "IEncoder.hpp"
#include "Error.hpp"
#include "data.h"

namespace Babel {
    namespace Codec {
        class Encoder : public Codec::IEncoder {
            public:
                Encoder() :
                    _error(0),
                    _state(opus_encoder_create(O_SAMPLE_RATE, O_NB_CHANNEL, O_APP, &_error))
                { checkError(); };
                ~Encoder()
                { opus_encoder_destroy(_state); }

                void checkError() const override
                {
                    if (_error < 0)
                        throw OpusError("Opus Error has occured. Error number: " + std::to_string(_error));
                }

                Packet encode(PCM const &pcm) override
                {
                    Packet encoded(O_DATA_SIZE);
                    opus_int32 len = opus_encode_float(_state, pcm.data(), O_FPB, encoded.data(), O_DATA_SIZE);

                    if (len < 0)
                        throw OpusError("Error when encoding: " + std::to_string(len));
                    return (Packet(encoded.begin(), encoded.begin() + len));
                }

                std::vector<Packet> encodeList(std::vector<PCM> const &pcms) override
                {
                    std::vector<Packet> packets(pcms.size());

                    for (std::size_t i = 0; i < pcms.capacity(); ++i)
                        packets[i] = (*this)(pcms[i]);
                    return (packets);
                }

                Packet operator()(PCM const &pcm) override
                { return (encode(pcm)); }

                std::vector<Packet> operator()(std::vector<PCM> const &pcms) override
                { return (encodeList(pcms)); }

            private:
                int _error;
                OpusEncoder *_state;
        };
    }
}

#endif /* !ENCODER_HPP_ */

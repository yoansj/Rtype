/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Stream
*/

#ifndef STREAM_HPP_
#define STREAM_HPP_

#include <iostream>
#include "Global.hpp"
#include "data.h"

namespace Babel {
    namespace Audio {
        enum E_PaStreamParameters {
            Null = 0,
            Default = 1,
        };

        class Stream {
            public:
                Stream(callbackPtr cb, void *data) :
                    _stream(nullptr),
                    _inputParam(), _outputParam(),
                    _rate(PA_SAMPLE_RATE), _framePerBuffer(PA_FPB),
                    _cb(cb), _data(data)
                { };
                ~Stream() = default;

                void setInputParam(E_PaStreamParameters param)
                {
                    if (param == E_PaStreamParameters::Default) _inputParam = getDefaultInputParam();
                    else _inputParam = PaStreamParameters{ .device = -1 };
                }

                void setOutputParam(E_PaStreamParameters param)
                {
                    if (param == E_PaStreamParameters::Default) _outputParam = getDefaultOutputParam();
                    else _outputParam = PaStreamParameters{ .device = -1 };
                }

                PaError openStream()
                {
                    return (Pa_OpenStream(
                        &_stream,
                        _inputParam.device == -1 ? nullptr : &_inputParam,
                        _outputParam.device == -1 ? nullptr : &_outputParam,
                        _rate, _framePerBuffer, paNoFlag,
                        _cb, _data
                    ));
                };
                PaError closeStream() { return (Pa_CloseStream(_stream)); };

                PaError startStream() { return (Pa_StartStream(_stream)); };
                PaError stopStream() { return (Pa_StopStream(_stream)); };

            private:
                PaStream *_stream;
                PaStreamParameters _inputParam;
                PaStreamParameters _outputParam;
                double _rate;
                std::size_t _framePerBuffer;
                callbackPtr _cb;
                void *_data;
        };
    }
}

#endif /* !STREAM_HPP_ */

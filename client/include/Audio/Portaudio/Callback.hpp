/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Callback
*/

#ifndef CALLBACK_HPP_
#define CALLBACK_HPP_

#include <portaudio.h>
#include "data.h"

namespace Babel {
    namespace Audio {
        /*
        **  Since we're using a VOIP Protocol, with an continuous and possibly endless stream
        **  Callback MUST always return paContinue to not stop the stream
        */

        static int paInputCallback(const void *inputBuffer, void *,
            unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *,
            PaStreamCallbackFlags, void *userData)
        {
            paData *data = (paData *)userData;
            float *ptr = &data->samples[data->frameIndex * 2];
            const float *input = (const float *)inputBuffer;

            if (!inputBuffer) {
                for(unsigned long i = 0; i < framesPerBuffer; ++i) {
                    *(ptr++) = PA_SILENCE;
                    *(ptr++) = PA_SILENCE;
                }
            } else {
                for(unsigned long i = 0; i < framesPerBuffer; ++i) {
                    *(ptr++) = *(input++);
                    *(ptr++) = *(input++);
                }
            }
            data->frameIndex += framesPerBuffer;
            return (paContinue);
        }

        static int paOutputCallback(const void *, void *outputBuffer,
            unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *,
            PaStreamCallbackFlags, void *userData)
        {
            paData *data = (paData *)userData;
            float *ptr = &data->samples[data->frameIndex * 2];
            float *out = (float *)outputBuffer;
            unsigned long i = 0;

            if (data->frameIndex * 2 >= data->maxFrameIndex) {
                for(; i < framesPerBuffer; i++) {
                    *(out++) = PA_SILENCE;
                    *(out++) = PA_SILENCE;
                }
                return (paContinue);
            }
            for(; i < framesPerBuffer; i++) {
                *(out++) = *(ptr++);
                *(out++) = *(ptr++);
            }
            data->frameIndex += framesPerBuffer;
            return (paContinue);
        }
    }
}

#endif /* !CALLBACK_HPP_ */

/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** data
*/

#ifndef PA_DATA_H_
#define PA_DATA_H_

#define PA_SAMPLE_RATE (48000)     // Sample Rate in Hz
#define PA_FPB (960)               // Frame Per Buffer
#define PA_SILENCE (0.0f)          // Silence: no sound
#define PA_BUFFER_SIZE (PA_SAMPLE_RATE * 2)

#include <vector>

namespace Babel {
    namespace Audio {
        using callbackPtr = int (*)(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);

        typedef struct paData {
            paData() :
                frameIndex(0), maxFrameIndex(0),
                samples(PA_BUFFER_SIZE) { };

            int frameIndex;
            int maxFrameIndex;
            std::vector<float> samples;
        } paData;
    }
}

#endif /* !PA_DATA_H_ */

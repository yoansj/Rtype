/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Global
*/

#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#include <iostream>
#include <portaudio.h>
#include "Error.hpp"

namespace Babel {
    namespace Audio {
        static PaStreamParameters getDefaultInputParam() {
            PaDeviceInfo const *info;
            int nbDevice = Pa_GetDeviceCount();
            PaStreamParameters inputParameters;

            if (nbDevice < 0) throw PortaudioError("No device found");

            for (int i = 0; i < nbDevice; ++i) {
                info = Pa_GetDeviceInfo(i);
                if(i == Pa_GetDefaultInputDevice() || i == Pa_GetHostApiInfo(info->hostApi)->defaultInputDevice) {
                    return (PaStreamParameters{
                        .device = i,
                        .channelCount = 2,
                        .sampleFormat = paFloat32,
                        .suggestedLatency = Pa_GetDeviceInfo(i)->defaultLowOutputLatency,
                        .hostApiSpecificStreamInfo = nullptr
                    });
                }
            }
            throw PortaudioError("No default input device found");
            return (PaStreamParameters{ .device = -1 });
        }

        static PaStreamParameters getDefaultOutputParam() {
            PaDeviceInfo const *info;
            int nbDevice = Pa_GetDeviceCount();
            PaStreamParameters inputParameters;

            if (nbDevice < 0) throw PortaudioError("No device found");

            for (int i = 0; i < nbDevice; ++i) {
                info = Pa_GetDeviceInfo(i);
                if(i == Pa_GetDefaultOutputDevice() || i == Pa_GetHostApiInfo(info->hostApi)->defaultOutputDevice) {
                    return (PaStreamParameters{
                        .device = i,
                        .channelCount = 2,
                        .sampleFormat = paFloat32,
                        .suggestedLatency = Pa_GetDeviceInfo(i)->defaultLowOutputLatency,
                        .hostApiSpecificStreamInfo = nullptr
                    });
                }
            }
            throw PortaudioError("No default output device found");
            return (PaStreamParameters{ .device = -1 });
        }

        static void printDevices()
        {
            int i, numDevices, defaultDisplayed;
            const   PaDeviceInfo *deviceInfo;
            PaStreamParameters inputParameters, outputParameters;

            std::cout << "PortAudio version: 0x" << Pa_GetVersion() << "\n";
            std::cout << "Version text: '" << Pa_GetVersionInfo()->versionText << "'\n";

            numDevices = Pa_GetDeviceCount();
            std::cout << "Number of devices = " << numDevices << "\n";

            for(i = 0; i < numDevices; i++)
            {
                deviceInfo = Pa_GetDeviceInfo(i);
                std::cout << "--------------------------------------- device #" << i << "\n";

                defaultDisplayed = 0;
                if( i == Pa_GetDefaultInputDevice() ) {
                    std::cout << "[ Default Input";
                    defaultDisplayed = 1;
                } else if( i == Pa_GetHostApiInfo( deviceInfo->hostApi )->defaultInputDevice ) {
                    const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo( deviceInfo->hostApi );
                    std::cout << "[ Default " << hostInfo->name << " Input";
                    defaultDisplayed = 1;
                }

                if(i == Pa_GetDefaultOutputDevice()) {
                    std::cout << (defaultDisplayed ? "," : "[");
                    std::cout << " Default Output";
                    defaultDisplayed = 1;
                } else if(i == Pa_GetHostApiInfo( deviceInfo->hostApi )->defaultOutputDevice) {
                    const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo( deviceInfo->hostApi );
                    std::cout << (defaultDisplayed ? "," : "[");
                    std::cout << " Default " << hostInfo->name << " Output";
                    defaultDisplayed = 1;
                }

                if( defaultDisplayed )
                    std::cout << " ]\n";

#ifdef WIN32
                {   /* Use wide char on windows, so we can show UTF-8 encoded device names */
                    wchar_t wideName[MAX_PATH];
                    MultiByteToWideChar(CP_UTF8, 0, deviceInfo->name, -1, wideName, MAX_PATH-1);
                    wprintf( L"Name                        = %s\n", wideName );
                }
#else
                std::cout << "Name                        = " << deviceInfo->name << "\n";
#endif
                std::cout << "Host API                    = " << Pa_GetHostApiInfo( deviceInfo->hostApi )->name << "\n";
                std::cout << "Max inputs = " << deviceInfo->maxInputChannels;
                std::cout << ", Max outputs = " << deviceInfo->maxOutputChannels << "\n";
                std::cout << "Default low input latency   = " << deviceInfo->defaultLowInputLatency << "\n";
                std::cout << "Default low output latency  = " << deviceInfo->defaultLowOutputLatency << "\n";
                std::cout << "Default high input latency  = " << deviceInfo->defaultHighInputLatency << "\n";
                std::cout << "Default high output latency = " << deviceInfo->defaultHighOutputLatency << "\n";
                std::cout << "Default sample rate         = " << deviceInfo->defaultSampleRate << "\n";
            }
        }
    }
}

#endif /* !GLOBAL_HPP_ */

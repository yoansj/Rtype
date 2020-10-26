/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Portaudio
*/

#ifndef PORTAUDIO_HPP_
#define PORTAUDIO_HPP_

#include <portaudio.h>
#include <map>
#include <memory>

#include "Stream.hpp"
#include "Callback.hpp"

namespace Babel {
    namespace Audio {
        class Portaudio {
            public:
                Portaudio();
                ~Portaudio();

                std::shared_ptr<Stream> const &getStream(std::size_t id) const;

                void openStream(std::size_t id, std::shared_ptr<Stream> const &stream, bool startAtOpen = false);
                void openOStream(std::size_t id, bool startAtOpen = false);
                void openIStream(std::size_t id, bool startAtOpen = false);

                void stopAllStreams();
                void closeAllStreams();

                void print(std::size_t id);

                std::vector<float> getPCM(std::shared_ptr<paData> const &, int) const;
                std::vector<std::vector<float>> getPCMs(std::size_t id) const;
                void setPCMs(std::size_t id, std::vector<std::vector<float>> const &);

            private:
                PaError _err;
                std::map<std::size_t, std::shared_ptr<Stream>> _streamMap;
                std::map<std::size_t, std::shared_ptr<paData>> _dataMap;

                void checkErrors() const { if (_err != paNoError) throw PortaudioError(Pa_GetErrorText(_err)); };
        };
    }
}

#endif /* !PORTAUDIO_HPP_ */

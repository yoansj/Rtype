/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Portaudio
*/

#include "Portaudio.hpp"

namespace Babel {
    namespace Audio {
        Portaudio::Portaudio()
        {
            _err = Pa_Initialize();
            checkErrors();
        }

        Portaudio::~Portaudio()
        {
            closeAllStreams();
            _err = Pa_Terminate();
            checkErrors();
        }

        std::shared_ptr<Stream> const &Portaudio::getStream(std::size_t id) const
        {
            auto it = _streamMap.find(id);

            if (it == _streamMap.end())
                throw PortaudioError("Stream '" + std::to_string(id) + "' not initialized");
            return (it->second);
        }

        void Portaudio::openStream(std::size_t id, std::shared_ptr<Stream> const &stream, bool startAtOpen)
        {
            if (_streamMap.find(id) != _streamMap.end())
                throw PortaudioError("Stream '" + std::to_string(id) + "' already exists");
            _streamMap.insert({ id, stream });
            _err = _streamMap[id]->openStream();
            checkErrors();
            if (startAtOpen) {
                _err = _streamMap[id]->startStream();
                checkErrors();
            }
        }

        void Portaudio::openOStream(std::size_t id, bool startAtOpen)
        {
            _dataMap.insert({ id, std::make_shared<paData>() });

            std::shared_ptr<Stream> stream = std::make_shared<Stream>(paOutputCallback, _dataMap[id].get());
            stream->setInputParam(E_PaStreamParameters::Null);
            stream->setOutputParam(E_PaStreamParameters::Default);
            openStream(id, stream, startAtOpen);
        }

        void Portaudio::openIStream(std::size_t id, bool startAtOpen)
        {
            _dataMap.insert({ id, std::make_shared<paData>() });

            std::shared_ptr<Stream> stream = std::make_shared<Stream>(paInputCallback, _dataMap[id].get());
            stream->setInputParam(E_PaStreamParameters::Default);
            stream->setOutputParam(E_PaStreamParameters::Null);
            openStream(id, stream, startAtOpen);
        }

        void Portaudio::stopAllStreams()
        {
            for (auto const &[id, stream] : _streamMap)
                stream->stopStream();
        }

        void Portaudio::closeAllStreams()
        {
            stopAllStreams();
            for (auto const &[id, stream] : _streamMap)
                stream->closeStream();
            _streamMap.clear();
            _dataMap.clear();
        }

        void Portaudio::print(std::size_t id)
        {
            auto p = _dataMap[id];

            for (std::size_t i = 0; i < p->frameIndex; ++i) {
                std::cout << p->samples[i] << std::endl;
            }
        }

        std::vector<float> Portaudio::getPCM(std::shared_ptr<paData> const &data, int nbSample) const
        {
            std::vector<float> pcm(PA_FPB * 2);

            for (int i = 0; i < PA_FPB * 2; ++i)
                *(pcm.data() + i) = data->samples[nbSample * PA_FPB * 2 + i];
            return (pcm);
        }

        std::vector<std::vector<float>> Portaudio::getPCMs(std::size_t id) const
        {
            auto it = _dataMap.find(id);
            if (it == _dataMap.end())
                throw PortaudioError("Couldn't get PCM of stream: " + std::to_string(id));

            std::vector<std::vector<float>> pcms(it->second->frameIndex / PA_FPB);

            for (int i = 0; i < pcms.capacity(); ++i)
                pcms[i] = getPCM(it->second, i);

            for (std::size_t i = 0; i < it->second->frameIndex; ++i)
                it->second->samples[i] = PA_SILENCE;
            it->second->frameIndex = 0;
            return (pcms);
        }

        void Portaudio::setPCMs(std::size_t id, std::vector<std::vector<float>> const &pcms)
        {
            auto it = _dataMap.find(id);
            if (it == _dataMap.end())
                throw PortaudioError("Couldn't set PCM of stream: " + std::to_string(id));

            auto data = it->second;
            std::vector<float> replacement(PA_BUFFER_SIZE, PA_SILENCE);

            if (data->frameIndex * 2 == data->maxFrameIndex) {
                data->maxFrameIndex = 0;
                data->frameIndex = 0;
            } else if (data->frameIndex * 2 < data->maxFrameIndex) {
                for (int i = data->frameIndex * 2; i < data->maxFrameIndex; ++i)
                    *(data->samples.data() + (i - data->frameIndex * 2)) = *(data->samples.data() + i);
                data->maxFrameIndex -= data->frameIndex * 2;
                data->frameIndex = 0;
            }
            for (std::size_t i = 0; i < pcms.size(); ++i) {
                for (std::size_t j = 0; j < PA_FPB * 2; ++j)
                    data->samples[i * PA_FPB * 2 + j] = *(pcms[i].data() + j);
                data->maxFrameIndex += PA_FPB * 2;
            }
        }
    }
}
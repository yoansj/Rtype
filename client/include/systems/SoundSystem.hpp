/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SoundSytem
*/

#ifndef SOUNDSYSTEM_HPP_
#define SOUNDSYSTEM_HPP_

#include <string>
#include <memory>
#include <SFML/Audio.hpp>

#include "System.hpp"
#include "Sound.hpp"
#include "EngineError.hpp"

namespace Engine {

class SoundSystem : public System<Sound> {
    public:
        SoundSystem();
        ~SoundSystem() = default;

        void update() {};

        void setSound(Entity e, std::string const &filepath);

        void playSound(Entity e);

        void stopSound(Entity e);

    protected:
    private:
};
}

#endif /* !SOUNDSYSTEM_HPP_ */

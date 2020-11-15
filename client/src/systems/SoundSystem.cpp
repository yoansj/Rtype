/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SoundSystem
*/

#include "SoundSystem.hpp"

Engine::SoundSystem::SoundSystem() : System()
{
}

void Engine::SoundSystem::setSound(Entity e, std::string const &filepath, bool isLoop)
{
    auto &component = _components.getComponent(e);

    component.buffer.loadFromFile(filepath);
    component.sound.setBuffer(component.buffer);
    component.sound.setLoop(isLoop);
    component.sound.setVolume(20);
}

void Engine::SoundSystem::playSound(Entity e)
{
    auto &component = _components.getComponent(e);

    component.sound.play();
}

void Engine::SoundSystem::stopSound(Entity e)
{
    auto &component = _components.getComponent(e);

    component.sound.stop();
}
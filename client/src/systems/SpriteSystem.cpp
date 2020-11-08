/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SpriteSystem
*/

#include "SpriteSystem.hpp"

Engine::SpriteSystem::SpriteSystem() : System()
{
}

bool Engine::SpriteSystem::initSprite(Entity e, std::string const &filepath)
{
    auto &component = _components.getComponent(e);

    //std::cout << "Entity: " << component.entity << " Filepath: " << filepath << std::endl;
    if (!component.texture.loadFromFile(filepath)) {
        throw EngineError("Sprite loading error", "Couldn't load sprite of filepath : " + filepath);
    } else {
        component.sprite.setTexture(component.texture, true);
        component.isCreated = true;
        component.animated = false;
    }
    return (true);
}

void Engine::SpriteSystem::update()
{
}

void Engine::SpriteSystem::createAnimation(Entity e, std::vector<sf::IntRect> frames)
{
    auto &component = _components.getComponent(e);

    //Animation newAnimation;

    //newAnimation.setSpriteSheet(component.texture);
    for (int i = 0; i != frames.size(); i++) {
        //newAnimation.addFrame(frames[i]);
    }
    //component.animations.push_back(newAnimation);
}

void Engine::SpriteSystem::setAnimationSpeed(Entity e, float speed)
{
    auto &component = _components.getComponent(e);

    component.animationSpeed = speed;
    //component.animatedSprite.setFrameTime(sf::seconds(speed));
}

void Engine::SpriteSystem::setPlayingAnimation(Entity e, int index)
{
    auto &component = _components.getComponent(e);

    //component.animatedSprite.play(component.animations[index]);
}
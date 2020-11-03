/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "Component.hpp"

#include <string>
#include <SFML/Graphics.hpp>

namespace Engine {

    struct Sprite : public Component {
        std::string filepath;
        bool isCreated;
        sf::Texture texture;
        sf::Sprite sprite;
    };

}
#endif /* !SPRITE_HPP_ */

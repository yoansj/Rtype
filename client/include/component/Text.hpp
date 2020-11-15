/*
** EPITECH PROJECT, 2020
** client
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "Component.hpp"

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

namespace Engine {

    /**
     * @brief Component Text
     * 
     */
    struct Text : public Component {
        //Filepath of the texture
        std::string filepath;

        // For Text
        bool isCreated;
        sf::Font font;
        sf::Text text;

    };

}

#endif /* !TEXT_HPP_ */

/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "Component.hpp"

#include <string>
#include <vector>
#include <SFML/Audio.hpp>


namespace Engine {

    /**
     * @brief Component Sound
     * 
     */
    struct Sound : public Component {
        //Filepath of the music
        sf::SoundBuffer buffer;

        // For music
        sf::Sound sound;

    };

}

#endif /* !SOUND_HPP_ */

/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** Packages
*/

#ifndef PACKAGES_HPP_
#define PACKAGES_HPP_

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

constexpr std::size_t bufferSize = 4096;

typedef struct connectionToServer_s {
    int type_struct;
    char message[128];
} connectionToServer_t;

typedef struct dataPlayersConnected_s {
    int type_struct;
    std::vector<sf::Sprite> players;
    char message[128];
} dataPlayersConnected_t;

/* ----TCP PACKAGE---- */

typedef struct createNewGame_s {
    int type_struct;
    char message[128];
} createNewGame_t;

typedef struct replyGameCreated_s {
    int type_struct;
    std::size_t idGame;
    char message[128];
} replyGameCreated_t;

typedef struct connectionGame_s {
    int type_struct;
    std::size_t idGame;
    char message[128];
} connectionGame_t;

typedef struct startNewGame_s {
    int type_struct;
    std::size_t idGame;
    char message[128];
} startNewGame_t;

typedef struct startedGame_s {
    int type_struct;
    std::vector<sf::Sprite> players;
    char message[128];
} startedGame_t;

#endif /* !PACKAGES_HPP_ */

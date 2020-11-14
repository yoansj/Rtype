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

#include "Position.hpp"
#include "PackagesType.hpp"

constexpr std::size_t bufferSize = 4096;

typedef struct dataPlayersConnected_s {
    int type_struct = 1;
    std::vector<sf::Sprite> players;
    char message[128];
} dataPlayersConnected_t;

/* ----TCP PACKAGE---- */

// Paquet envoyé par le client
// Lorsqu'il souhaite créer une partie
// TCP
typedef struct createNewGame_s {
    int type_struct = 2;
    char message[128];
} createNewGame_t;

// Paquet envoyé par le serveur
// Lorsqu'un client a créé une partie
// Contient l'ID de la partie et l'index du joueur
// TCP
typedef struct replyGameCreated_s {
    int type_struct = 3;
    std::size_t idGame;
    int playerIndex;
    char message[128];
} replyGameCreated_t;

// Paquet envoyé par le serveur
// Une fois qu'il s'est connecté à la partie
// Lorsqu'il souhaite rejoindre une partie
// Avec le bouton join lobby
// TCP
typedef struct connectionGame_s {
    int type_struct = 4;
    std::size_t idGame;
    int playerIndex;
    char message[128];
} connectionGame_t;

// Paquet envoyé par le client
// Lorsqu'il souhaite rejoindre une partie
typedef struct joinGame_s {
    int type_struct = 8;
    std::size_t idGame;
} joinGame_t;

// Paquet envoyé par le client
// Lorsqu'il souhaite commencer une partie
// TCP
typedef struct startNewGame_s {
    int type_struct = 5;
    std::size_t idGame = -1;
    char message[128];
} startNewGame_t;

// Pas encore utilisé
typedef struct gameStarted_s {
    int type_struct = 6;
    int nbPlayers = 1;
    char message[128];
} gameStarted_t;



/* UDP */

// Paquet de position
typedef struct position_s {
    int type_struct = 7;
    int senderIndex;
    std::size_t gameId;
    Engine::Position pos;
} position_t;

#endif /* !PACKAGES_HPP_ */

/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TcpHandler
*/

#include "TcpHandler.hpp"

void TcpHandler::run()
{
    std::cout << "test" << std::endl;
    std::thread receiverHandler([this](std::vector<tcp::socket> &_sockets) {
        while (1) {
            for (unsigned int i = 0; i < _sockets.size(); i += 1) {
                std::string tmp = "Salut";
                boost::system::error_code ignored_error;
                boost::asio::write(_sockets.at(i), boost::asio::buffer(tmp), ignored_error);
            }
        }
    }, std::ref(_sockets));
    receiverHandler.detach();
    while (1) {
        tcp::socket socket(_io_service);
        _acceptor.accept(socket);
        _sockets.push_back(std::move(socket));
        std::cout << _sockets.size() << std::endl;
    }


    // while (1) {
    //     tcp::socket socket(_io_service);
    //     _acceptor.accept(socket);
    //     _sockets.push_back(std::move(socket));
    //     _sockets.back().receive(boost::asio::buffer(_buffer, sizeof(int)));
    //     getTypePackage();
    // }
}

void TcpHandler::acceptor(void)
{
    while (1)
    {
        tcp::socket socket(_io_service);
        _acceptor.accept(socket);
        _sockets.push_back(std::move(socket));
        // _sockets.back().receive(boost::asio::buffer(_buffer, sizeof(int)));
        // getTypePackage();
    }
}

void TcpHandler::getTypePackage(void)
{
    int type_struct;

    std::memcpy(&type_struct, &_buffer, sizeof(int));
    if (type_struct == CREATE_NEW_GAME)
        createNewGame(type_struct);
    if (type_struct == START_NEW_GAME)
        startNewGame(type_struct);
}

void TcpHandler::listNewGame(void)
{
    std::size_t nbGameRunning = _lobbyList.size();
    replyGameCreated_t reply;

    reply = (replyGameCreated_t){REPLY_GAME_CREATED, nbGameRunning, "REPLY_GAME_CREATED"};
    _lobbyList.insert({nbGameRunning, std::vector<tcp::endpoint>{_sockets.back().remote_endpoint()}});
    std::cout << _lobbyList.size() << std::endl;
    _sockets.back().send(boost::asio::buffer(&reply, sizeof(replyGameCreated_t)));
}

void TcpHandler::createNewGame(int type_struct)
{
    std::array<char, sizeof(createNewGame_t)> tmp;
    createNewGame_t package;

    package.type_struct = type_struct;
    _sockets.back().receive(boost::asio::buffer(tmp.data(), sizeof(createNewGame_t) - sizeof(int)));
    std::memcpy(reinterpret_cast<char *>(&package) + sizeof(int), tmp.data(), (sizeof(createNewGame_t) - sizeof(int)));
    std::cout << package.message << std::endl;
    listNewGame();
}

void TcpHandler::startNewGame(int type_struct)
{
    std::array<char, sizeof(startNewGame_t)> tmp;
    startNewGame_t package;

    package.type_struct = type_struct;
    _sockets.back().receive(boost::asio::buffer(tmp.data(), sizeof(startNewGame_t) - sizeof(int)));
    std::memcpy(reinterpret_cast<char *>(&package) + sizeof(int), tmp.data(), (sizeof(startNewGame_t) - sizeof(int)));
    std::cout << package.message << std::endl;
    //startGame(package.idGame);
}

// void TcpHandler::startGame(std::size_t idGame)
// {
//     std::size_t i = _gameRunning.size();
//     _gameRunning.insert({ idGame, std::thread([this](std::map<std::size_t, std::vector<tcp::endpoint>> &listPlayers, std::size_t idGame) {
//             while (1)
//                 std::cout << "game_running" << std::endl;
//         }, std::ref(_gameRunning), idGame)
//         });
//         _gameRunning[i].detach();
// }

// Template T, T = structure paquet
// Dans le switch call fonction template <mettre le type de la struct>
// std::array<char, sizeof(T)> & remplacer tous les types de structure pas T et la fonction return la nouvelle struct
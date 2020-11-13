/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TcpManager
*/

#include "TcpManager.hpp"

TcpManager::TcpManager(boost::asio::io_service &service, std::vector<void *> &pkg, std::map<std::size_t, std::shared_ptr<ServerGame>> &games) :
_ios(service), _packagesList(pkg), _acceptor(_ios, tcp::endpoint(tcp::v4(), 7172)), _games(games)
{
    try {
        _acceptor.non_blocking(true);
    } catch (boost::system::error_code &err) {
        std::cout << "Throw dans le constructeur " << std::endl;
    }
}


void TcpManager::acceptConnections()
{
    tcpSocket newCli = std::make_shared<tcp::socket>(_ios);

    try {
        _acceptor.accept(*newCli.get());
        if (newCli->is_open()) {
            std::cout << "New client Ip: " << newCli->remote_endpoint().address() << " Port: " << newCli->remote_endpoint().port() << std::endl;
            newCli->non_blocking(true);
            _clients.push_back(newCli);
        }
    } catch (boost::wrapexcept<boost::system::system_error> &err) {
        // if (err == boost::asio::error::try_again) {
        //     std::cout << err.message() << std::endl;
        // } else {
        //     //throw err;
        // }
        if (err.code() == boost::asio::error::try_again) {
            //std::cout << "Try again okay !" << std::endl;
        } else {
            throw err;
        }
    }
}

void TcpManager::receivePackages()
{
    // Boucle et reçoit les paquets tcp de tous les clients
    for (int i = 0; i != _clients.size(); i++) {
        if (!_clients[i]->is_open()) {
            std::cout << "Client disconnected Ip: " << _clients[i]->remote_endpoint().address() << " Port: " << _clients[i]->remote_endpoint().port() << std::endl;
        } else {
            getPackageType(_clients[i], i);
        }
    }
}

void TcpManager::getPackageType(tcpSocket &cli, std::size_t index)
{
    int type_struct;
    std::array<char, sizeof(int)> buffer;

    try {
        cli->receive(boost::asio::buffer(buffer.data(), sizeof(int)));
        std::memcpy(&type_struct, buffer.data(), sizeof(int));
        if (type_struct == CREATE_NEW_GAME) {
            auto pkg = loadPkgType<createNewGame_t>(cli);
            handlePackage(pkg, cli);
        }
        if (type_struct == START_NEW_GAME) {
            auto pkg = loadPkgType<startNewGame_t>(cli);
            handlePackage(pkg, cli);
        }
    } catch (boost::wrapexcept<boost::system::system_error> &err) {
        if (err.code() == boost::asio::error::try_again) {
            //std::cout << "Try again okay !" << std::endl;
        } else if (err.code() == boost::asio::error::eof) {
            std::cout << "Client disconnected Ip: " << cli->remote_endpoint().address() << " Port: " << cli->remote_endpoint().port() << std::endl;
        } else
            throw err;
    }
}

template <class PkgType>
PkgType TcpManager::loadPkgType(tcpSocket &cli)
{
    PkgType pkg;

    cli->receive(boost::asio::buffer(reinterpret_cast<char *>(&pkg) + sizeof(int), sizeof(PkgType) - sizeof(int)));
    return (pkg);
}

void TcpManager::handlePackage(createNewGame_t &package, tcpSocket &cli)
{
    // Création de la partie
    // Création du thread de la partie
    // Ajout de la partie dans la liste des parties
    auto newGame = std::make_shared<ServerGame>(cli, _games.size());
    _games.insert(std::pair<std::size_t, std::shared_ptr<ServerGame>>(_games.size(), newGame));
    std::thread gameThread(&ServerGame::run, &(*newGame.get()));
    gameThread.detach();

    // Répondre a l'utilisateur que la partie a été créée avec l'id de la partie
    replyGameCreated_t reply = {REPLY_GAME_CREATED, newGame->getId(), "REPLY_GAME_CREATED"};
    cli->send(boost::asio::buffer(&reply, sizeof(replyGameCreated_t)));
}

void TcpManager::handlePackage(startNewGame_t &package, tcpSocket &cli)
{
    // Récupérer la partie dans la map
    // Commencer la partie
    // Les paquets seront envoyés par la fonction start game à l'avenir

    std::cout << "Game id: " << package.idGame << std::endl;
    auto result = _games.find(package.idGame);
    if (result != _games.end()) {
        gameStarted_t reply = {STARTED_GAME, "GAME STARTED"};
        result->second->startGame();
        cli->send(boost::asio::buffer(&reply, sizeof(gameStarted_t)));
    }
}
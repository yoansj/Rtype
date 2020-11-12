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

void TcpManager::connectionHandler(tcpSocket &newCli, const boost::system::error_code& error)
{
    // if (!error) {
    //     std::cout << "New client received connection accepted !" << std::endl;
    //     newCli->non_blocking(true);
    //     _clients.push_back(newCli);
    //     receivePackages();
    //     std::cout << "Clients: " << _clients.size() << std::endl;
    // } else {
    //     std::cout << "Error : " << error.message() << std::endl;
    // }
    // acceptConnections();
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

void TcpManager::receiveTypeHandler(std::array<char, sizeof(int)> &type, tcpSocket &newCli, const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        std::cout << "Received data" << std::endl;

        int type_struct = 42;
        std::memcpy(&type_struct, &_buffer, sizeof(int));

        if (type_struct == CREATE_NEW_GAME) {
            loadPkgType<createNewGame_t>(newCli, CREATE_NEW_GAME);
        }
        if (type_struct == START_NEW_GAME)
            std::cout << "Start game !" << std::endl;

    } else {
        std::cout << "Error : " << error.message() << std::endl;
    }
    receivePackages();
}

void TcpManager::receivePackages()
{
    // Boucle et reçoit les paquets tcp de tous les clients
    for (int i = 0; i != _clients.size(); i++) {
        if (!_clients[i]->is_open()) {
            std::cout << "Client disconnected Ip: " << _clients[i]->remote_endpoint().address() << " Port: " << _clients[i]->remote_endpoint().port() << std::endl;
        } else {
            getPackageType(_clients[i]);
        }
    }
}

void TcpManager::getPackageType(tcpSocket &cli)
{
    int type_struct;
    std::array<char, sizeof(int)> buffer;

    try {
        cli->receive(boost::asio::buffer(buffer.data(), sizeof(int)));
        std::memcpy(&type_struct, buffer.data(), sizeof(int));
        if (type_struct == CREATE_NEW_GAME)
            loadPkgType<createNewGame_t>(cli, CREATE_NEW_GAME);
        if (type_struct == START_NEW_GAME)
            std::cout << "Start game !" << std::endl;
    } catch (boost::wrapexcept<boost::system::system_error> &err) {
        if (err.code() == boost::asio::error::try_again) {
            //std::cout << "Try again okay !" << std::endl;
        } else {
            throw err;
        }
    }
}

template <class PkgType>
void TcpManager::loadPkgType(tcpSocket &cli, PackagesType type)
{
    PkgType pkg;

    cli->receive(boost::asio::buffer(reinterpret_cast<char *>(&pkg) + sizeof(int), sizeof(PkgType) - sizeof(int)));
    pkgHandler(pkg, cli, type);
}

template <class PkgType>
void TcpManager::pkgHandler(PkgType &package, tcpSocket &cli, PackagesType type)
{
    if (type == CREATE_NEW_GAME) {
        // Création de la partie
        // Création du thread de la partie
        // Ajout de la partie dans la liste des parties
        auto newGame = std::make_shared<ServerGame>(cli, _games.size());
        _games.insert(std::pair<std::size_t, std::shared_ptr<ServerGame>>(_games.size(), newGame));
        std::thread gameThread(&ServerGame::run, &(*newGame.get()));
        gameThread.detach();

        // Répondre a l'utilisateur que la partie a été créée avec l'id de la partie
        replyGameCreated_t reply;
        reply = (replyGameCreated_t){REPLY_GAME_CREATED, newGame->getId(), "REPLY_GAME_CREATED"};
        cli->send(boost::asio::buffer(&reply, sizeof(replyGameCreated_t)));
    }
}
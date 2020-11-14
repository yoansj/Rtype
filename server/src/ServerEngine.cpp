/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ServerEngine
*/

#include "ServerEngine.hpp"

ServerEngine::ServerEngine() :
_acceptor(_ios, tcp::endpoint(tcp::v4(), 7172)),
_udpServer(_ios, udp::endpoint(udp::v4(), 7172))
{
    try {
        _acceptor.non_blocking(true);
        _udpServer.non_blocking(true);
    } catch (boost::system::error_code &err) {
        std::cout << "Throw dans le constructeur " << std::endl;
    }
}

void ServerEngine::acceptConnections()
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
        if (err.code() == boost::asio::error::try_again) {
            //std::cout << "Try again okay !" << std::endl;
        } else {
            throw err;
        }
    }
}

void ServerEngine::receiveTcpPackages()
{
    // Boucle et reçoit les paquets tcp de tous les clients
    for (int i = 0; i != _clients.size(); i++) {
        if (!_clients[i]->is_open()) {
            std::cout << "Client disconnected Ip: " << _clients[i]->remote_endpoint().address() << " Port: " << _clients[i]->remote_endpoint().port() << std::endl;
        } else {
            getPackageType(_clients[i], i);
        }
    }
    disconnectClients();
}

void ServerEngine::receiveUdpPackages()
{
    std::array<char, 10000> buffer;
    udp::endpoint endpoint;
    boost::system::error_code error;

    _udpServer.receive_from(boost::asio::buffer(buffer), endpoint, 0, error);

    if (error == boost::asio::error::try_again)
        return;

    int code = *reinterpret_cast<int *>(buffer.data());

    // Recevoir un paquet position
    if (code == POSITION_PACKAGE) {
        position_t *package = (position_t*)reinterpret_cast<char *>(buffer.data());
        auto game = _games.find(package->gameId);
        if (game != _games.end()) {
            game->second->addPackage({POSITION_PACKAGE, package});
        }
    }
}

void ServerEngine::disconnectClients()
{
    for (int i = 0; i != _clientsToDisconnect.size(); i++) {
        _clients.erase(_clients.begin() + _clientsToDisconnect[i]);
    }
    _clientsToDisconnect.clear();
}

void ServerEngine::getPackageType(tcpSocket &cli, std::size_t index)
{
    int type_struct;
    std::array<char, sizeof(int)> buffer;

    try {
        /*
            terminate called after throwing an instance of 'boost::wrapexcept<boost::system::system_error>'
            what():  receive: Connection reset by peer
            ./run_server: line 8: 12412 Aborted                 (core dumped) ./build/bin/r-type_server $1
        */
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
        if (type_struct == JOIN_GAME_PACKAGE) {
            auto pkg = loadPkgType<joinGame_t>(cli);
            handlePackage(pkg, cli);
        }
    } catch (boost::wrapexcept<boost::system::system_error> &err) {
        if (err.code() == boost::asio::error::try_again) {
        } else if (err.code() == boost::asio::error::eof) {
            std::cout << "Client disconnected Ip: " << cli->remote_endpoint().address() << " Port: " << cli->remote_endpoint().port() << std::endl;
            _clientsToDisconnect.push_back(index);
        } else
            throw err;
    }
}

template <class PkgType>
PkgType ServerEngine::loadPkgType(tcpSocket &cli)
{
    PkgType pkg;

    cli->receive(boost::asio::buffer(reinterpret_cast<char *>(&pkg) + sizeof(int), sizeof(PkgType) - sizeof(int)));
    return (pkg);
}

void ServerEngine::handlePackage(createNewGame_t &package, tcpSocket &cli)
{
    // Création de la partie
    // Création du thread de la partie
    // Ajout de la partie dans la liste des parties

    auto newGame = std::make_shared<ServerGame>(cli, _games.size());
    newGame->addPlayer(cli);
    _games.insert(std::pair<std::size_t, std::shared_ptr<ServerGame>>(_games.size(), newGame));
    std::thread gameThread(&ServerGame::run, &(*newGame.get()));
    gameThread.detach();

    // Répondre a l'utilisateur que la partie a été créée avec l'id de la partie
    replyGameCreated_t reply = {REPLY_GAME_CREATED, newGame->getId(), 0, "REPLY_GAME_CREATED"};
    cli->send(boost::asio::buffer(&reply, sizeof(replyGameCreated_t)));
}

void ServerEngine::handlePackage(startNewGame_t &package, tcpSocket &cli)
{
    // Récupérer la partie dans la map
    // Commencer la partie
    // Les paquets seront envoyés par la fonction start game à l'avenir

    std::cout << "START GAME ID: " << package.idGame << std::endl;
    auto result = _games.find(package.idGame);
    if (result != _games.end()) {
        result->second->startGame();
        //  gameStarted_t reply = {STARTED_GAME, 1, "GAME STARTED"};
        // cli->send(boost::asio::buffer(&reply, sizeof(gameStarted_t)));
    }
}

void ServerEngine::handlePackage(joinGame_t &package, tcpSocket &cli)
{
    // Récupérer la partie
    // Ajouter le joueur dans la partie
    // Répondre qu'il a rejoint la partie

    std::cout << "CONNECTION TO GAME ID: " << package.idGame << std::endl;
    auto result = _games.find(package.idGame);
    if (result != _games.end()) {
        connectionGame_t reply = {CONNECTION_TO_GAME, result->second->getId(), result->second->addPlayer(cli) ,"CONNECTED TO GAME"};
        cli->send(boost::asio::buffer(&reply, sizeof(gameStarted_t)));
    }
}

void ServerEngine::run()
{
    std::cout << "Server start ! Ip : " << _acceptor.local_endpoint().address() << ":" << _acceptor.local_endpoint().port() << std::endl;
    while (1) {
        acceptConnections();
        receiveTcpPackages();
        receiveUdpPackages();
    }
}
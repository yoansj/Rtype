/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

UdpServer::UdpServer::UdpServer(boost::asio::io_service& io_service) :
    _socket(io_service, udp::endpoint(udp::v4(), 7171))
{
    UdpServer::startReceive();
}

void UdpServer::startReceive()
{
    _socket.async_receive_from(boost::asio::buffer(_buffer), _remote_endpoint,
        boost::bind(&UdpServer::handleReceive, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handleReceive(const boost::system::error_code &error, std::size_t bytes)
{
    int type_struct;

    std::memcpy(&type_struct, &_buffer, sizeof(int));
    if (type_struct == CREATE_NEW_GAME)
        listNewGame();
    if (!error || error == boost::asio::error::message_size) {
        boost::shared_ptr<std::string> message(new std::string("100, 100"));
        _socket.async_send_to(boost::asio::buffer(*message), _remote_endpoint,
                                boost::bind(&UdpServer::handleSend, this, message,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
        UdpServer::startReceive();
    }
}

void UdpServer::handleSend(boost::shared_ptr<std::string> msg,
                            const boost::system::error_code & err,
                            std::size_t bytes)
{
    send("game_create");
}

void UdpServer::listNewGame(void)
{
    std::cout << players.size() << std::endl;
    std::size_t nbGameRunning = _listGameRuning.size();

    _listGameRuning.insert({ nbGameRunning + 1,  std::thread([this](std::vector<int>& players) {
            this->print();
            players.push_back(1);
        }, std::ref(players))
        });
        _listGameRuning[nbGameRunning + 1].join();
        std::cout << players.size() << std::endl;
}

void UdpServer::print(void)
{
    std::cout << "coucou" << std::endl;
}

void UdpServer::send(std::string message)
{
    _socket.send_to(boost::asio::buffer(message, message.size()), _remote_endpoint);
}
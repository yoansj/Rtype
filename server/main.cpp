/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** main
*/

#include <boost/asio.hpp>
#include "UdpServer.hpp"

int main(int argc, char **argv)
{
    boost::asio::io_service io_service;
    UdpServer server(io_service);

    try {
        if (argc != 2) {
            std::cerr << "Error try: ./run_server <port>" << std::endl;
            return 0;
        } else {
            std::thread thread([&io_service]() { io_service.run(); });
            thread.join();
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
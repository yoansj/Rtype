/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** main
*/

#include <boost/asio.hpp>
#include <iostream>
// #include <thread>
#include <memory>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>


#include "UdpServer.hpp"

// Connection -> Nombre de client connecté, la couleur (bleu/rouge/vert/jaune), vector Sprite joueur connecté
// Position joueurs & information joueur
// Position des monstres & information des monstres

int main(int argc, char **argv)
{
    try {
        boost::asio::io_service io_service;
        UdpServer server(io_service);
        boost::thread_group threads;
        // boost::thread_attributes :
        for (unsigned i = 0; i < stack_size; ++i)
            threads.add_thread(bind(&asio::io_service::run, &io_service));
        threads.join_all();
        // std::thread thread1([&io_service]() { io_service.run(); });
        // std::thread thread2([&io_service]() { io_service.run(); });
        // thread1.join();
        // thread2.join();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
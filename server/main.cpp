/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** main
*/

#include <array>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <memory>

using boost::asio::ip::udp;

struct data {
    int type_message;
    int struct_type;
    char message[2000];
};

class udp_server
{
    public:
        udp_server(boost::asio::io_service &io_service)
            : socket_(io_service, udp::endpoint(udp::v4(), 7171))
        {
            start_receive();
        }

        void do_send( std::string message)
        {
            socket_.send_to(boost::asio::buffer(message, message.size()), remote_endpoint_);
        }

    private:
        void start_receive()
        {
            socket_.async_receive_from(boost::asio::buffer(buffer), remote_endpoint_,
                boost::bind(&udp_server::handle_receive, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
        }

    void handle_receive(const boost::system::error_code &error, std::size_t bytes)
    {
        struct data tmp;

        memcpy(&tmp, &buffer, buffer.size());
        std::cout << tmp.message <<std::endl;
        if (!error || error == boost::asio::error::message_size)
        {
            boost::shared_ptr<std::string> message(
                new std::string("100, 100"));
            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                                    boost::bind(&udp_server::handle_send, this, message,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> msg,
                        const boost::system::error_code & err,
                        std::size_t bytes)
    {
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::array<char, 1024> buffer;
};

int main(int argc, char **argv)
{
    try {
        boost::asio::io_service io_service;
        udp_server server(io_service);
        std::thread thread1([&io_service]() { io_service.run(); });
        std::thread thread2([&io_service]() { io_service.run(); });
        thread1.join();
        thread2.join();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
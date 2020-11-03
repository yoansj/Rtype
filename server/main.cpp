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

using boost::asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server
{
public:
    udp_server(boost::asio::io_service &io_service)
        : socket_(io_service, udp::endpoint(udp::v4(), 7171))
    {
        start_receive();
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_), remote_endpoint_,
            boost::bind(&udp_server::handle_receive, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code &error,
                        std::size_t bytes)
    {
        if (!error || error == boost::asio::error::message_size)
        {
            auto buffer_begin = std::cbegin(recv_buffer_), buffer_end = std::cend(recv_buffer_);
            std::cout << "Buffer :" << std::string(recv_buffer_.begin(), bytes)
            << " Error code :" << error
            << " Bytes : " << bytes
            << " Endpoint : " << remote_endpoint_
            << std::endl;
            boost::shared_ptr<std::string> message(
                new std::string(make_daytime_string()));
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
    boost::array<char, 128> recv_buffer_;
};

int main(int argc, char **argv)
{
    try {
        boost::asio::io_service io_service;
        udp_server server(io_service);
        io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
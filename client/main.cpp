/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** main
*/

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class UDPClient
{
    public:
        UDPClient(
            boost::asio::io_service& io_service,
            const std::string& host,
            const std::string& port
        ) : io_service_(io_service), socket_(io_service, udp::endpoint(udp::v4(), 0)) {
            udp::resolver resolver(io_service_);
            udp::resolver::query query(udp::v4(), host, port);
            udp::resolver::iterator iter = resolver.resolve(query);
            endpoint_ = *iter;
        }

	~UDPClient()
	{
		socket_.close();
	}

	void send(const std::string& msg) {
		socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_);
	}

    void receive(void)
    {
        boost::array<char, 128> recv_buf;
        udp::endpoint sender_endpoint;
        size_t len = socket_.receive_from(
            boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout.write(recv_buf.data(), len);
    }

    private:
        boost::asio::io_service& io_service_;
        udp::socket socket_;
        udp::endpoint endpoint_;
};

int main(int argc, char **argv)
{
	boost::asio::io_service io_service;
	UDPClient client(io_service, "localhost", argv[1]);

	client.send("Hello, World!");
    while (1) {
        client.receive();
    }
}
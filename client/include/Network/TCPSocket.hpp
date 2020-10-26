/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** TCPSocket
*/

#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include <QTcpSocket>

#include "ClientSocket.hpp"

namespace Babel {
    namespace Network {
        class TCPSocket : public ClientSocket<QTcpSocket> {
            Q_OBJECT

            public:
                TCPSocket() : ClientSocket()
                {
                    connect(_socket.get(), SIGNAL(connected()), this, SLOT(connected()));
                    connect(_socket.get(), SIGNAL(disconnected()), this, SLOT(disconnected()));
                    // connect(_socket.get(), SIGNAL(errorOccurred(SocketError)), this, SLOT(errorOccurred()));
                };
                ~TCPSocket()
                { disconnect(); }

                std::shared_ptr<QTcpSocket> &getSocket()
                { return (_socket); }

                void write(std::string const &packet)
                { _socket->write(packet.data(), packet.size()); }

                void write(int code, Packet::Bson const &bson)
                { write(Packet::build_message(code, bson)); }

                void connectToAddr(std::string const &addr, int port = NETCL_TCP_PORT)
                { _socket->connectToHost(addr.data(), port); }

                void disconnect()
                { _socket->disconnectFromHost(); }

            public slots:
                void connected()
                { qDebug() << "connected to " << _socket->peerAddress().toString() << _socket->peerPort(); }

                void disconnected()
                { qDebug() << "disconnected from " << _socket->peerAddress().toString(); }

                void errorOccurred(QAbstractSocket::SocketError socketError)
                { throwNetworkError(_socket->errorString()); }
        };

        static std::shared_ptr<TCPSocket> createTCPSocket()
        { return (std::make_shared<TCPSocket>()); }
    }
}

#endif /* !TCPSOCKET_HPP_ */

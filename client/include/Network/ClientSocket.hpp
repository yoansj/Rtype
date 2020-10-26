/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** ClientSocket
*/

#ifndef CLIENTSOCKET_HPP_
#define CLIENTSOCKET_HPP_

#include <QHostAddress>
#include <QAbstractSocket>
#include <QDebug>

#include "IClientSocket.hpp"
#include "Error.hpp"
#include "Conversion.hpp"
#include "Bson.hpp"

namespace Babel {
    namespace Network {
        template <class T, bool B = std::is_base_of<QAbstractSocket, T>::value>
        class ClientSocket;

        template <class T>
        class ClientSocket<T, true> : public QObject, public IClientSocket {
            public:
                ClientSocket() : QObject(), _socket(std::make_shared<T>())
                {}
                virtual ~ClientSocket() = default;

                virtual void connectToAddr(std::string const &addr, int port = NETCL_TCP_PORT) = 0;

                virtual void disconnect() = 0;

                virtual void write(std::string const &packet) = 0;

                std::string read() { return (""); };

                void throwNetworkError(std::string const &err)
                { throw NetworkError(err); }

                void throwNetworkError(QString const &err)
                { throwNetworkError(err.toStdString()); }

            public slots:
                virtual void connected() = 0;
                virtual void disconnected() = 0;
                virtual void errorOccurred(QAbstractSocket::SocketError) = 0;

            protected:
                std::shared_ptr<T> _socket;
        };
    }
}

#endif /* !CLIENTSOCKET_HPP_ */

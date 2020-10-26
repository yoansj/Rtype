/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** UDPSocket
*/

#ifndef UDPSOCKET_HPP_
#define UDPSOCKET_HPP_

#include <QUdpSocket>
#include <QTimer>

#include "ClientSocket.hpp"

namespace Babel {
    namespace Network {
        class UDPSocket : public ClientSocket<QUdpSocket> {
            Q_OBJECT

            public:
                UDPSocket(QHostAddress const &addr = QHostAddress::LocalHost) :
                    ClientSocket(), _socket(std::make_shared<QUdpSocket>()),
                    _timer(std::make_shared<QTimer>())
                {
                    _socket->bind(addr);
                    _myAddress = _socket->localAddress();
                    _myPort = _socket->localPort();

                    // if (_serverAddr == QHostAddress("127.0.0.1") || _serverAddr == QHostAddress::LocalHost) _serverAddr = QHostAddress("::ffff:127.0.0.1");

                    // std::string packet(Packet::Bson::turn_into_byte_string<int>(NETCL_UDP_MAGIC));
                    // _socket->writeDatagram(packet.data(), packet.size(), _serverAddr, _serverPort);

                    // connect(_socket.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));
                    connect(_timer.get(), SIGNAL(timeout()), this, SLOT(update()));
                    _timer->start(1000);
                };
                ~UDPSocket()
                { disconnect(); }

                std::shared_ptr<QUdpSocket> &getSocket() { return _socket; }

                void write(std::string const &packet)
                {
                    for (auto const &[pseudo, ip] : _addrList)
                        _socket->writeDatagram(packet.data(), packet.size(), ip.first, ip.second);
                }

                std::string read()
                {
                    QHostAddress senderAddr;
                    quint16 senderPort;
                    int code = -1;

                    while (_socket->hasPendingDatagrams()) {
                        std::string packet(_socket->pendingDatagramSize(), ' ');
                        _socket->readDatagram(packet.data(), _socket->pendingDatagramSize(), &senderAddr, &senderPort);

                        qDebug() << "Packet:" << packet.data();
                    }
                    return ("");
                }

                void addIpToList(std::string const &pseudo, QHostAddress const &addr, quint16 port)
                { _addrList.insert({ pseudo, { addr, port } }); }

                void removeIpToList(std::string const &pseudo)
                { _addrList.erase(pseudo); }

                void clearIpList() { _addrList.clear(); }

                void connectToAddr(std::string const &, int) { }
                void disconnect() { }

            public slots:
                void connected() { }
                void disconnected() { }
                void errorOccurred(QAbstractSocket::SocketError) { }

                void readyRead()
                { read(); }

                void update()
                {
                    write("Hello from " + _myAddress.toString().toStdString() + " " + std::to_string(_myPort));
                }

            private:
                std::shared_ptr<QUdpSocket> _socket;
                QHostAddress _myAddress;
                quint16 _myPort;
                std::map<std::string, std::pair<QHostAddress, quint16>> _addrList;
                std::shared_ptr<QTimer> _timer;

            // private:
            //     bool isHostInList(QHostAddress addr, quint16 port)
            //     {
            //         for (auto const &[_addr, _port] : _addrList)
            //             if (_addr == addr && _port == port)
            //                 return (true);
            //         return (false);
            //     }

            //     void decodeServerUDPMessage(std::string const &packet, int const &code)
            //     {
            //         if (code == 506) UDP::infoCallSend(packet, _addrList);
            //         if (code == 507) UDP::infoCallDistribution(packet, _addrList);
            //     }

            //     void decodeClientUDPMessage(std::string const &packet, int const &code)
            //     {
            //     }
        };

        static std::shared_ptr<UDPSocket> createUDPSocket(QHostAddress const &addr = QHostAddress::LocalHost)
        { return (std::make_shared<UDPSocket>(addr)); }
    }
}

#endif /* !UDPSOCKET_HPP_ */

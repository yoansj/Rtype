/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** NetworkManager
*/

#ifndef NETWORKMANAGER_HPP_
#define NETWORKMANAGER_HPP_

#include <QObject>

#include "TCPSocket.hpp"
#include "UDPSocket.hpp"
#include "Cache.hpp"
#include "Bson.hpp"
#include "Conversion.hpp"

namespace Babel {
    class NetworkManager : public QObject {
        Q_OBJECT

        public:
            NetworkManager() : QObject(), _cache(Cache::Cache::Get()),
                _tcpSocket(Network::createTCPSocket()), _udpSocket(Network::createUDPSocket()),
                _callbackMap{
                    std::make_pair(201, &NetworkManager::getGroup), std::make_pair(202, &NetworkManager::getProfile), std::make_pair(203, &NetworkManager::userAddedToGroup),
                    std::make_pair(204, &NetworkManager::userLeftGroup), std::make_pair(205, &NetworkManager::addContact), std::make_pair(206, &NetworkManager::deleteContact),
                    std::make_pair(207, &NetworkManager::getGroups), std::make_pair(208, &NetworkManager::getContacts), std::make_pair(501, &NetworkManager::notifCall),
                    std::make_pair(503, &NetworkManager::quitCall), std::make_pair(505, &NetworkManager::requestInfoCall), (std::make_pair(507, &NetworkManager::distributeInfoCall))
                },
                _errorCallbackMap{
                    std::make_pair(401, &NetworkManager::errorPseudoAlreadyExist), std::make_pair(402, &NetworkManager::errorAuthentificationFailed),
                    std::make_pair(403, &NetworkManager::errorMessageNotSend), std::make_pair(404, &NetworkManager::errorCallFailed),
                    std::make_pair(405, &NetworkManager::errorProfilNotAdded), std::make_pair(406, &NetworkManager::errorContactNotExist),
                    std::make_pair(407, &NetworkManager::errorUserAlreadyExist)
                }
            {
                connect(_tcpSocket->getSocket().get(), SIGNAL(readyRead()), this, SLOT(readTcpSocket()));
                _tcpSocket->connectToAddr("127.0.0.1", 15565);
            }
            ~NetworkManager() = default;

            std::string getUdpAddress() { return(_udpSocket->getSocket()->localAddress().toString().toStdString()); };
            int getUdpPort() { return(_udpSocket->getSocket()->localPort()); };

        private:
            Cache::Cache &_cache;
            std::shared_ptr<Network::TCPSocket> _tcpSocket;
            std::shared_ptr<Network::UDPSocket> _udpSocket;
            std::map<int, void (NetworkManager::*)(Packet::Bson const &)> _callbackMap;
            std::map<int, void (NetworkManager::*)(bool)> _errorCallbackMap;

        signals:
            void pseudoAlreadyExist(bool b);
            void authentificationFailed(bool b);
            void messageNotSend(bool b);
            void callFailed(bool b);
            void profilNotAdded(bool b);
            void contactNotExist(bool b);
            void userAlreadyExist(bool b);

        private slots:
            void readTcpSocket()
            {
                qDebug() << "\n================================";
                qDebug() << "Debut:" << _tcpSocket->getSocket()->bytesAvailable();
                int messageType = bytesToNumerical<int>(_tcpSocket->getSocket()->read(sizeof(int)));
                qDebug() << "Code:" << messageType;

                if (_errorCallbackMap.find(messageType) != _errorCallbackMap.end()) {
                    (this->*(_errorCallbackMap[messageType]))(true);
                    _tcpSocket->getSocket()->readAll();
                } else {
                    std::size_t messageSize = bytesToNumerical<std::size_t>(_tcpSocket->getSocket()->read(sizeof(std::size_t)));
                    std::string message(_tcpSocket->getSocket()->read(messageSize - sizeof(std::size_t)), messageSize - sizeof(std::size_t));

                    std::string fullMessage((Packet::Bson::turn_into_byte_string(messageSize) + message).data(), messageSize);
                    Packet::Bson bson(fullMessage);

                    auto it = _callbackMap.find(messageType);

                    if (it != _callbackMap.end())
                        (this->*(it->second))(bson);
                }
                qDebug() << "End:" << _tcpSocket->getSocket()->bytesAvailable();
                qDebug() << "================================\n";
                if (_tcpSocket->getSocket()->bytesAvailable() != 0)
                    readTcpSocket();
            }

        public:
            // Code: 601
            void createProfile(std::string const &pseudo, std::string const &password)
            { _tcpSocket->write(601, Packet::Bson("pseudo", pseudo, "password", password)); }

            // Code: 602
            void ammendProfile(std::string const &pseudo, std::string const &password, int const &pp)
            { _tcpSocket->write(602, Packet::Bson("pseudo", pseudo, "password", password, "pp", pp)); }

            // Code: 603
            void createGroup(std::string const &groupName)
            { _tcpSocket->write(603, Packet::Bson("group_name", groupName)); }

            // Code: 604
            void addContactToGroup(std::size_t const &idGroup, std::string const &pseudo)
            { _tcpSocket->write(604, Packet::Bson("id_group", idGroup, "pseudo", pseudo)); }

            // Code: 605
            void quitGroup(std::size_t const &idGroup, std::string const &pseudo)
            { _tcpSocket->write(605, Packet::Bson("id_group", idGroup, "pseudo", pseudo)); }

            // Code: 606
            void addContactSender(std::string const &pseudo)
            { _tcpSocket->write(606, Packet::Bson("pseudo", pseudo)); }

            // Code: 607
            void deleteContactSender(std::string const &pseudo)
            { _tcpSocket->write(607, Packet::Bson("pseudo", pseudo)); }

            // Code: 608
            void login(std::string const &pseudo, std::string const &password)
            {
                _cache.getObject("profil")->changeValueOfObject<std::string>("password", password);
                _tcpSocket->write(608, Packet::Bson("pseudo", pseudo, "password", password));
            }

        private:
            // Code: 201
            void getGroup(Packet::Bson const &bson)
            {
                auto arr = _cache.getArray<std::shared_ptr<Json::Object>>("groupes");
                std::string idGroup = bson.find<std::string>("id_group");

                for (std::size_t i = 0; i < arr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*arr)[i]->getPropertyFromObject("id_group"));
                    if (value && value->getData() == idGroup)
                        return;
                }
                std::vector<Packet::Bson> v = bson.find<std::vector<Packet::Bson>>("list");
                auto json_arr = Json::createArray<std::string>("list");

                for (std::size_t i = 0; i < v.size(); ++i)
                    json_arr += v[i].find<std::string>("pseudo");
                auto obj = Json::createObject("",
                    std::make_pair("id_group", bson.find<std::string>("id_group")),
                    std::make_pair("group_name", bson.find<std::string>("group_name")),
                    std::make_pair("last_update_date", bson.find<std::string>("last_update_date")),
                    std::make_pair("status", 0)
                );
                obj->addPropertyToObject(json_arr);
                arr->addData(obj);
            }

            // Code: 202
            void getProfile(Packet::Bson const &bson)
            {
                std::string myPseudo = _cache.getValue<std::string>("pseudo", "profil")->getData();

                if (myPseudo != "") {
                    addContact(bson);
                } else {
                    _cache.getObject("profil")->changeValueOfObject<std::string>("pseudo", bson.find<std::string>("pseudo"));
                    _cache.getObject("profil")->changeValueOfObject<int>("pp", bson.find<std::size_t>("pp"));
                    _cache.getObject("profil")->changeValueOfObject<int>("status", bson.find<std::size_t>("status"));
                }
                pseudoAlreadyExist(false);
            }

            // Code: 203
            void userAddedToGroup(Packet::Bson const &bson)
            {
                auto arr = _cache.getArray<std::shared_ptr<Json::Object>>("groupes");

                for (std::size_t i = 0; i < arr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*arr)[i]->getPropertyFromObject("id_group"));

                    if (value->getData() == bson.find<std::string>("id_group"))
                        std::dynamic_pointer_cast<Json::Array<std::string>>((*arr)[i]->getPropertyFromObject("user_list")) += bson.find<std::string>("pseudo");
                }
            }

            // Code: 204
            void userLeftGroup(Packet::Bson const &bson)
            {
                std::string myPseudo = _cache.getValue<std::string>("pseudo", "profil")->getData();
                auto arr = _cache.getArray<std::shared_ptr<Json::Object>>("groupes");
                std::size_t i = 0;

                for (; i < arr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*arr)[i]->getPropertyFromObject("id_group"));

                    if (value->getData() == bson.find<std::string>("id_group"))
                        break;
                }
                if (myPseudo == bson.find<std::string>("id_group"))
                    arr->eraseValue(i);
                else
                    std::dynamic_pointer_cast<Json::Array<std::string>>((*arr)[i]->getPropertyFromObject("user_list"))->eraseValue(bson.find<std::string>("pseudo"));
            }

            // Code: 205
            void addContact(Packet::Bson const &bson)
            {
                std::string myPseudo = _cache.getValue<std::string>("pseudo", "profil")->getData();
                auto arr = _cache.getArray<std::shared_ptr<Json::Object>>("contact_list");

                for (std::size_t i = 0; i < arr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*arr)[i]->getPropertyFromObject("pseudo"));

                    if (value->getData() == bson.find<std::string>("pseudo") || bson.find<std::string>("pseudo") == myPseudo)
                        return;
                }

                auto obj = Json::createObject("",
                    std::make_pair("pseudo", bson.find<std::string>("pseudo")),
                    std::make_pair("pp", static_cast<int>(bson.find<std::size_t>("pp"))),
                    std::make_pair("status", static_cast<int>(bson.find<std::size_t>("status"))),
                    std::make_pair("id_group", "0")
                );
                arr->addData(obj);
                errorProfilNotAdded(false);
            }

            // Code: 206
            void deleteContact(Packet::Bson const &bson)
            {
                auto arr = _cache.getArray<std::shared_ptr<Json::Object>>("contact_list");

                for (std::size_t i = 0; i < arr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*arr)[i]->getPropertyFromObject("pseudo"));

                    if (value->getData() == bson.find<std::string>("pseudo")) {
                        arr->eraseValue(i);
                        break;
                    }
                }
            }

            // Code: 207
            void getGroups(Packet::Bson const &bson)
            {
                std::vector<Packet::Bson> v = bson.find<std::vector<Packet::Bson>>("list");

                for (auto const &e : v)
                    getGroup(e);
                authentificationFailed(false);
            }

            // Code: 208
            void getContacts(Packet::Bson const &bson)
            {
                std::vector<Packet::Bson> v = bson.find<std::vector<Packet::Bson>>("list");

                for (auto const &e : v)
                    addContact(e);
            }

        public:
            // Code: 501
            void notifCallSender(std::string const &idGroup, std::vector<std::string> const &listPseudo, std::string const &addr, int port)
            {
                _tcpSocket->write(501, Packet::Bson("id_group", idGroup, "list_pseudo", listPseudo, "address", addr, "port", port));
                std::string myPseudo = _cache.getValue<std::string>("pseudo", "profil")->getData();
                auto groupeArr = _cache.getArray<std::shared_ptr<Json::Object>>("groupes");

                for (std::size_t i = 0; i < groupeArr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*groupeArr)[i]->getPropertyFromObject("id_group"));
                    if (value && value->getData() == idGroup) {
                        (*groupeArr)[i]->changeValueOfObject("status", 1);
                        return;
                    }
                }

                bool me = myPseudo == listPseudo[1];
                auto ctcArr = _cache.getArray<std::shared_ptr<Json::Object>>("contact_list");

                for (std::size_t i = 0; i < ctcArr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*ctcArr)[i]->getPropertyFromObject("pseudo"));
                    if (value && value->getData() == listPseudo[!me])
                        (*ctcArr)[i]->changeValueOfObject("id_group", idGroup);
                }
            }

            // Code: 501
            void notifCall(Packet::Bson const &bson)
            {
                std::string myPseudo = _cache.getValue<std::string>("pseudo", "profil")->getData();
                auto groupeArr = _cache.getArray<std::shared_ptr<Json::Object>>("groupes");

                for (std::size_t i = 0; i < groupeArr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*groupeArr)[i]->getPropertyFromObject("id_group"));
                    if (value && value->getData() == bson.find<std::string>("id_group")) {
                        (*groupeArr)[i]->changeValueOfObject("status", 1);
                        return;
                    }
                }

                std::vector<std::string> v = bson.find<std::vector<std::string>>("list_pseudo");
                bool me = myPseudo == v[1];
                auto ctcArr = _cache.getArray<std::shared_ptr<Json::Object>>("contact_list");

                for (std::size_t i = 0; i < ctcArr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*ctcArr)[i]->getPropertyFromObject("pseudo"));
                    if (value && value->getData() == v[!me])
                        (*ctcArr)[i]->changeValueOfObject("id_group", bson.find<std::string>("id_group"));
                }
            }

            // Code: 502
            void acceptCall(std::string const &pseudo, std::string const &idGroup)
            { _tcpSocket->write(502, Packet::Bson("pseudo", pseudo, "id_group", idGroup)); }

            // Code: 503
            void quitCallSender(std::string const &pseudo, std::string const &idGroup)
            {
                _udpSocket->clearIpList();
                _tcpSocket->write(503, Packet::Bson("pseudo", pseudo, "id_group", idGroup));
            }

            // Code: 503
            void quitCall(Packet::Bson const &bson)
            {
                auto ctcArr = _cache.getArray<std::shared_ptr<Json::Object>>("contact_list");

                for (std::size_t i = 0; i < ctcArr->getSize(); ++i) {
                    auto value = std::dynamic_pointer_cast<Json::Value<std::string>>((*ctcArr)[i]->getPropertyFromObject("pseudo"));
                    if (value && value->getData() == bson.find<std::string>("pseudo"))
                        (*ctcArr)[i]->changeValueOfObject("id_group", std::string("0"));
                }
                _udpSocket->removeIpToList(bson.find<std::string>("pseudo"));
            }

            // Code: 505
            void requestInfoCall(Packet::Bson const &bson)
            {
                giveInfoCall(getUdpAddress(), getUdpPort(), bson.find<std::string>("id_group"));
            }

            // Code: 506
            void giveInfoCall(std::string const &addr, int port, std::string const &idGroup)
            { _tcpSocket->write(506, Packet::Bson("address", addr, "port", port, "id_group", idGroup)); }


            // Code: 507
            void distributeInfoCall(Packet::Bson const &bson)
            {
                std::vector<Packet::Bson> v = bson.find<std::vector<Packet::Bson>>("list");

                for (auto const &bson : v) {
                    _udpSocket->addIpToList(
                        bson.find<std::string>("pseudo"),
                        QHostAddress(bson.find<std::string>("address").data()),
                        bson.find<std::size_t>("port")
                    );
                }
            }

            // Code: 401
            void errorPseudoAlreadyExist(bool b)
            { emit pseudoAlreadyExist(b); }

            // Code: 402
            void errorAuthentificationFailed(bool b)
            { emit authentificationFailed(b); }

            // Code: 403
            void errorMessageNotSend(bool b)
            { emit messageNotSend(b); }

            // Code: 404
            void errorCallFailed(bool b)
            { emit callFailed(b); }

            // Code: 405
            void errorProfilNotAdded(bool b)
            { emit profilNotAdded(b); }

            // Code: 406
            void errorContactNotExist(bool b)
            { emit contactNotExist(b); }

            // Code: 407
            void errorUserAlreadyExist(bool b)
            { emit userAlreadyExist(b); }
    };
}

#endif /* !NETWORKMANAGER_HPP_ */

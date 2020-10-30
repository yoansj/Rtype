/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

void Client::Systems::SystemManager::CreateSystem(std::shared_ptr<System> const &s) {
    _systems.insert(std::pair<std::string, std::shared_ptr<System>>(s->GetName(), s));
}

std::shared_ptr<Client::Systems::System> &Client::Systems::SystemManager::GetSystem(std::string systemName) {
    return (_systems.find(systemName)->second);
}

void Client::Systems::SystemManager::AddComponentToSystem(std::string systemName, std::shared_ptr<Components::Component> c) {
    if (_systems.find(systemName) == _systems.end()) {
        std::cout << "Error while adding component " << c->_name << " to system " << systemName << std::endl;
    } else
        _systems.find(systemName)->second->AddComponent(c);
}

void Client::Systems::SystemManager::Update() {
    for (auto i = _systems.begin(); i != _systems.end(); i++) {
        i->second->Update();
        //std::cout << "test" << std::endl;
    }
}
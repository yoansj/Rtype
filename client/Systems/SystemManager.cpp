/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

void Client::Systems::SystemManager::CreateSystem(System &s) {
    _systems.insert(std::pair<std::string, System&>(s.GetName(), s));
}

Client::Systems::System &Client::Systems::SystemManager::GetSystem(std::string systemName) {
    return (_systems.find(systemName)->second);
}

void Client::Systems::SystemManager::AddComponentToSystem(std::string systemName, Components::Component &c) {
    _systems.find(systemName)->second.AddComponent(c);
}

void Client::Systems::SystemManager::Update() {
    for (auto i = _systems.begin(); i != _systems.end(); i++) {
        i->second.Update();
    }
}
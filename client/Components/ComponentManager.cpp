/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

Client::Components::Component const &Client::Components::ComponentManager::CreateComponent(Component const &c) {
    // pour chaque système du composant
    // appeller la fonction de la factory de system
    // addTo system (qui prend une string qui est le nom du système dans lequel on add le composant)
    std::vector<std::shared_ptr <Systems::System>> systems;
    for (int i = 0; i != c._systems.size(); i++) {
        Systems::SystemManager::Get().AddComponentToSystem(c._systems[i], c);
        auto lol = std::make_shared<Systems::System>(Systems::SystemManager::Get().GetSystem(c._name));
        systems.push_back(lol);
    }
    auto cShared = std::make_shared<Component>(c);
    _components.insert(std::pair<std::shared_ptr<Component>, std::vector<std::shared_ptr<Systems::System>>>(cShared, systems));
    // _components.insert(std::pair<Component, std::vector<Systems::System>>(c, systems));
    return (c);
}   
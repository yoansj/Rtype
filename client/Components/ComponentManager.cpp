/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

std::shared_ptr <Client::Components::Component> const &Client::Components::ComponentManager::CreateComponent(std::shared_ptr<Component> const &c) {
    // pour chaque système du composant
    // appeller la fonction de la factory de system
    // addTo system (qui prend une string qui est le nom du système dans lequel on add le composant)
    std::vector<std::shared_ptr<Systems::System>> systems;
    for (int i = 0; i != c->_systems.size(); i++) {
        Systems::SystemManager::Get().AddComponentToSystem(c->_systems[i], c);
        systems.push_back(Systems::SystemManager::Get().GetSystem(c->_name));
    }
    _components.insert(std::pair<std::shared_ptr<Component>, std::vector<std::shared_ptr<Systems::System>>>(c, systems));
    return (c);
}
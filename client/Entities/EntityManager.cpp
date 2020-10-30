/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

Client::Entities::EntityManager::EntityManager()
{
}

std::shared_ptr<Client::Entities::Entity> Client::Entities::EntityManager::Create(std::vector<Components::Component> initComponents)
{
    auto newEntity = std::make_shared<Entity>(_minId, initComponents);
    _minId++;
    _entities.push_back(newEntity);
    return (newEntity);
}

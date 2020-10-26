/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Json
*/

#include "Cache.hpp"

namespace Babel {
    namespace Cache {
        Cache::Cache() : _data(Json::createObject("data")), _built(false)
        { buildFromFile(std::string(ROOT_PATH) + "client/json/DefaultCache.json"); }

        Cache::~Cache() { }

        Cache &Cache::Get()
        {
            static Cache _instance;
            return (_instance);
        }

        void Cache::buildFromFile(std::string const &filename)
        {
            _filename = filename;
            if (_built) return;
            Json::Parser::parse(filename, _data);
            _built = true;
        }

        void Cache::__forceRebuild__()
        {
            _built = false;
            _data = Json::createObject("data");
            buildFromFile(_filename);
        }

        std::shared_ptr<Json::Object> Cache::getObject(std::string const &name) const
        { return std::dynamic_pointer_cast<Json::Object>((*_data)[name]); }

        void Cache::addProperty(std::string const &name, std::string const &path)
        {
            _data->addPropertyToObject(Json::createObject(name), path);
        }

        void Cache::addProperty(std::shared_ptr<Json::Object> const &obj, std::string const &path)
        {
            _data->addPropertyToObject(obj, path);
        }

        void Cache::addCategory(std::string const &name)
        {
            addProperty(name);
        }

        void Cache::remove(std::string const &name, std::string const &path)
        {
            _data->deleteValueFromObject(name, path);
        }

        std::shared_ptr<Json::Property> const &Cache::operator[](std::string const &path)
        {
            return ((*_data)[path]);
        }
    }
}

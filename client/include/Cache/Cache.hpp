/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Cache
*/

#ifndef CACHE_HPP_
#define CACHE_HPP_

#include "Json.hpp"
#include "Parser.hpp"

namespace Babel {
    namespace Cache {
        class Cache {
            public:
                static Cache &Get();

                void buildFromFile(std::string const &);
                void __forceRebuild__();

                template <class T>
                std::shared_ptr<Json::Value<T>> getValue(std::string const &, std::string const & = "") const;
                template <class T>
                std::shared_ptr<Json::Array<T>> getArray(std::string const &, std::string const & = "") const;
                std::shared_ptr<Json::Object> getObject(std::string const &) const;

                template <class T>
                void addProperty(std::string const &, T const &, std::string const & = "");
                template <class T>
                void addProperty(std::string const &, std::vector<T> const &, std::string const & = "");
                void addProperty(std::shared_ptr<Json::Object> const &, std::string const & = "");
                void addProperty(std::string const &, std::string const & = "");

                void addCategory(std::string const &);
                template <class ...Args>
                void addCategory(std::string const &, std::string const &, Args const &...);
                template <class T, class ...Args>
                void addCategory(std::string const &, std::pair<std::string, T> const &, Args const &...);
                template <class ...Args>
                void addCategory(std::string const &, std::shared_ptr<Json::Object> const &, Args const &...);

                /*
                ** Prevent from error by casting 'const char *' to 'std::string'
                */
                template <class ...Args>
                void addCategory(std::string const &catName, char const * const &str, Args const &...args)
                { addCategory(catName, std::string(str), args...); }
                template <class T, class ...Args>
                void addCategory(std::string const &catName, std::pair<char const *, T> const &pair, Args const &...args)
                { addCategory(catName, std::pair<std::string, T>(pair), args...); }
                template <class ...Args>
                void addCategory(std::string const &catName, std::pair<std::string, char const *> const &pair, Args const &...args)
                { addCategory(catName, std::pair<std::string, std::string>(pair), args...); }

                template <class T>
                void edit(std::string const &, T const &, std::string const & = "");

                void remove(std::string const &, std::string const & = "");

                void print() { _data->print(); };
                void dump() { _data->dump(); };

                std::shared_ptr<Json::Property> const &operator[](std::string const &);

            private:
                std::shared_ptr<Json::Object> _data;
                bool _built;
                std::string _filename;

            private:
                Cache();
                ~Cache();
                Cache(Cache const &) = delete;
                Cache(Cache &&) = delete;
        };
    }
}

namespace Babel {
    namespace Cache {
        template <class T>
        std::shared_ptr<Json::Value<T>> Cache::getValue(std::string const &name, std::string const &path) const
        {
            return std::dynamic_pointer_cast<Json::Value<T>>((*_data)[path + "." + name]);
        }

        template <class T>
        std::shared_ptr<Json::Array<T>> Cache::getArray(std::string const &name, std::string const &path) const
        {
            return std::dynamic_pointer_cast<Json::Array<T>>((*_data)[path + "." + name]);
        }

        template <class T>
        void Cache::addProperty(std::string const &name, T const &value, std::string const &path)
        {
            _data->addPropertyToObject(Json::createValue(name, value), path);
        }

        template <class T>
        void Cache::addProperty(std::string const &name, std::vector<T> const &value, std::string const &path)
        {
            _data->addPropertyToObject(Json::createArray(name, value), path);
        }

        template <class ...Args>
        void Cache::addCategory(std::string const &catName, std::string const &obj, Args const &...args)
        {
            addProperty(obj, catName);
            addCategory(catName, args...);
        }

        template <class T, class ...Args>
        void Cache::addCategory(std::string const &catName, std::pair<std::string, T> const &pair, Args const &...args)
        {
            addProperty(pair.first, pair.second, catName);
            addCategory(catName, args...);
        }

        template <class ...Args>
        void Cache::addCategory(std::string const &catName, std::shared_ptr<Json::Object> const &obj, Args const &...args)
        {
            addProperty(obj, catName);
            addCategory(catName, args...);
        }

        template <class T>
        void Cache::edit(std::string const &name, T const &value, std::string const &path)
        {
            _data->changeValueOfObject(name, value, path);
        }
    }
}

#endif /* !CACHE_HPP_ */

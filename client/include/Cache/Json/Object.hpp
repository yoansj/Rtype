/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Object
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>
#include "String.hpp"
#include "Value.hpp"

namespace Babel {
    namespace Json {
        class Object : public Property {
            public:
                Object(std::string const &name) : Property(name, Type::_object), _object{ } { };

                Object(std::string const &name, std::vector<std::shared_ptr<Property>> const &arrayProps) :
                    Property(name, Type::_object), _object(arrayProps)
                { };

                ~Object() = default;

                std::shared_ptr<Property> const &getPropertyFromObject(std::string const &name, std::string const &path = "") const
                {
                    if (path != "") {
                        auto v = _split(path, ".");
                        for (auto const &e : _object)
                            if (e->getName() == v.front() && e->getType() == Type::_object)
                                return (std::dynamic_pointer_cast<Object>(e)->getPropertyFromObject(name, _join(std::vector<std::string>(v.begin() + 1, v.end()))));
                    }
                    for (auto const &e : _object)
                        if (e->getName() == name)
                            return (e);
                    return (__null__);
                };


                template <class ...Args>
                void managePath(std::string const &path, void (Object::*ptr)(Args const &...), Args const &... args)
                {
                    auto v = _split(path, ".");
                    for (auto const &e : _object)
                        if (e->getName() == v.front() && e->getType() == Type::_object) {
                            ((*std::dynamic_pointer_cast<Object>(e)).*ptr)(args...);
                            return;
                        } else if (e->getName() == v.front() && e->getType() != Type::_object)
                            return;
                    addPropertyToObject(std::make_shared<Object>(v.back()), _join(std::vector<std::string>(v.begin(), v.end() - 1), "."));
                    managePath(path, ptr, args...);
                    return;

                }

                void addPropertyToObject(std::shared_ptr<Property> const &prop, std::string const &path = "")
                {
                    if (path != "") {
                        std::string newPath = path.find(".") == std::string::npos ? "" : path.substr(path.find(".") + 1);
                        managePath(path, &Object::addPropertyToObject, prop, newPath);
                        return;
                    }
                    for (auto const &e : _object)
                        if (e->getName() == prop->getName())
                            return;
                    _object.push_back(prop);
                };

                template <class T>
                void changeValueOfObject(std::string const &name, T const &newData, std::string const &path = "")
                {
                    if (path != "") {
                        std::string newPath = path.find(".") == std::string::npos ? "" : path.substr(0, path.find("."));
                        managePath(path, &Object::changeValueOfObject, name, newData, newPath);
                        return;
                    }
                    for (auto const &e : _object) {
                        auto ptr = std::dynamic_pointer_cast<Value<T>>(e);
                        if (e->getName() == name && ptr) {
                            ptr->setData(newData);
                            return;
                        } else if (e->getName() == name && e->getType() != Type::_object && !ptr) {
                            deleteValueFromObject(name);
                            addPropertyToObject(std::make_shared<Value<T>>(name, newData));
                            return;
                        }
                    }
                    addPropertyToObject(std::make_shared<Value<T>>(name, newData));
                };

                void deleteValueFromObject(std::string const &name, std::string const &path = "")
                {
                    if (path != "") {
                        auto v = _split(path, ".");
                        deleteValueFromObject(v.front(), _join(std::vector<std::string>(v.begin() + 1, v.end())));
                    }
                    for (auto it = _object.begin(); it < _object.end(); ++it)
                        if ((*it)->getName() == name) {
                            _object.erase(it);
                            break;
                        }
                }

                void print(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    std::cout << std::string(base_indent, ' ') << '"' << _name;
                    if (_object.empty())
                        std::cout << "\": { }," << std::endl;
                    else {
                        std::cout << "\": {" << std::endl;
                        for (auto const &e : _object)
                            e->print(base_indent + indent_size);
                        std::cout << std::string(base_indent, ' ') << "}," << std::endl;
                    }
                }
                void dump(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    std::cout << std::string(base_indent, ' ') << '"' << _name << "\": {" << std::endl;
                    for (auto const &e : _object) {
                        std::cout << std::string(base_indent, ' ');
                        e->dump(base_indent + indent_size);
                    }
                    std::cout << std::string(base_indent, ' ') << "}," << std::endl;
                }

                Property const &operator=(std::shared_ptr<Property> const &prop) override { addPropertyToObject(prop); return (*this); };
                std::shared_ptr<Property> const &operator[](std::string const &path)
                {
                    std::vector<std::string> v = _split(path, ".");
                    return (getPropertyFromObject(v.back(), _join(std::vector<std::string>(v.begin(), v.end() - 1), ".")));
                };

            private:
                std::vector<std::shared_ptr<Property>> _object;

                std::shared_ptr<Property> __null__ = std::shared_ptr<Property>(nullptr);
        };

        static std::shared_ptr<Object> createObject(std::string const &name)
        {
            return (std::make_shared<Object>(name));
        }

        static std::shared_ptr<Object> createObject(std::string const &name, std::vector<std::shared_ptr<Property>> const &arrayProps)
        {
            return (std::make_shared<Object>(name, arrayProps));
        }

        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::shared_ptr<Object> const &objptr, Args const & ...args);

        template <class T, class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::pair<std::string, T> const &pair, Args const & ...args);

        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::string const &str, Args const & ...args);

        /*
        ** Prevent from error by casting 'const char *' to 'std::string'
        */
        template <class T, class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::pair<char const *, T> const &pair, Args const & ...args);
        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::pair<char const *, char const *> const &pair, Args const & ...args);
        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::pair<std::string, char const *> const &pair, Args const & ...args);
        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, char const * const &str, Args const & ...args);
    }
}

namespace Babel {
    namespace Json {
        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::shared_ptr<Object> const &objptr, Args const & ...args)
        {
            std::shared_ptr<Object> obj = createObject(name, args...);

            obj->addPropertyToObject(objptr);
            return (obj);
        }

        template <class T, class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::pair<std::string, T> const &pair, Args const & ...args)
        {
            std::shared_ptr<Object> obj = createObject(name, args...);

            obj->addPropertyToObject(createValue(pair.first, pair.second));
            return (obj);
        }

        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::string const &str, Args const & ...args)
        {
            std::shared_ptr<Object> obj = createObject(name, args...);

            obj->addPropertyToObject(createObject(str));
            return (obj);
        }

        /*
        ** Prevent from error by casting 'const char *' to 'std::string'
        */
        template <class T, class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::pair<char const *, T> const &pair, Args const & ...args)
        { return createObject(name, std::pair<std::string, T>(pair), args...); }

        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::pair<char const *, char const *> const &pair, Args const & ...args)
        { return createObject(name, std::pair<std::string, std::string>(pair), args...); }

        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, std::pair<std::string, char const *> const &pair, Args const & ...args)
        { return createObject(name, std::pair<std::string, std::string>(pair), args...); }

        template <class ...Args>
        static std::shared_ptr<Object> createObject(std::string const &name, char const * const &str, Args const & ...args)
        { return createObject(name, std::string(str), args...); }
    }
}

#endif /* !OBJECT_HPP_ */

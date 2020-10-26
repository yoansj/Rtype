/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Array
*/

#ifndef ARRAY_HPP_
#define ARRAY_HPP_

#include "String.hpp"
#include "Object.hpp"

namespace Babel {
    namespace Json {
        template <class T>
        class Array : public Property {
            public:
                Array(std::string const &name, std::vector<int> const &v = { }) :
                    Property(name, Type::_array, Type::_int), _data(v) { };
                Array(std::string const &name, std::vector<double> const &v = { }) :
                    Property(name, Type::_array, Type::_double), _data(v) { };
                Array(std::string const &name, std::vector<std::string> const &v = { }) :
                    Property(name, Type::_array, Type::_string), _data(v) { };
                ~Array() = default;

                std::size_t const getSize() const { return _data.size(); };
                T const &getData(std::size_t i) const { return _data[i]; };
                void setData(std::vector<T> const &data) { _data = data; }

                void addData(T const &data) { _data.push_back(data); }
                void addData(std::vector<T> const &data) { _data.insert(_data.end(), data.begin(), data.end()); }

                void eraseValue(std::size_t const &i) { _data.erase(_data.begin() + i); }
                void eraseValue(T const &value) { _data.erase(std::remove(_data.begin(), _data.end(), value), _data.end()); }

                void dump(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    std::cout << std::string(base_indent, ' ') << '"' << _name << "\": [" << std::endl;
                    for (auto const &e : _data)
                        std::cout << std::string(base_indent, ' ') << e << std::endl;
                    std::cout << std::string(base_indent, ' ') << "]," << std::endl;
                }

                void print(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    std::cout << std::string(base_indent, ' ') << '"' << _name;
                    if (_data.empty())
                        std::cout << "\": [ ]," << std::endl;
                    else {
                        std::cout << "\": [" << std::endl;
                        for (auto const &e : _data) {
                            auto str = _subType == Type::_string ? ('"' + e + '"') : e;
                            std::cout << std::string(base_indent + indent_size, ' ') << str << "," << std::endl;
                        }
                        std::cout << std::string(base_indent, ' ') << "]," << std::endl;
                    }
                }

                Property const &operator=(std::vector<T> const &newData) override { setData(newData); return (*this); };
                Property const &operator+=(T const &newData) { addData(newData); return (*this); };
                Property const &operator+=(std::vector<T> const &newData) { addData(newData); return (*this); };
                T const &operator[](std::size_t const &i) { return (getData(i)); };

            private:
                std::vector<T> _data;
        };

        template <>
        class Array<std::shared_ptr<Object>> : public Property {
            public:
                Array(std::string const &name, std::vector<std::shared_ptr<Object>> const &v = std::vector<std::shared_ptr<Object>>()) :
                    Property(name, Type::_array, Type::_object), _data(v) { };
                ~Array() = default;

                std::size_t const getSize() const { return _data.size(); };
                std::shared_ptr<Object> const &getData(std::size_t i) const { return _data[i]; };
                void setData(std::vector<std::shared_ptr<Object>> const &data) { _data = data; }

                void addData(std::shared_ptr<Object> const &data) { _data.push_back(data); }
                void addData(std::vector<std::shared_ptr<Object>> const &data) { _data.insert(_data.end(), data.begin(), data.end()); }

                void eraseValue(std::size_t const &i) { _data.erase(_data.begin() + i); }

                void dump(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    std::cout << std::string(base_indent, ' ') << '"' << _name << "\": [" << std::endl;
                    for (auto const &e : _data)
                        e->dump(base_indent + indent_size);
                    std::cout << std::string(base_indent, ' ') << "]," << std::endl;
                }

                void print(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    std::cout << std::string(base_indent, ' ') << '"' << _name;
                    if (_data.empty())
                        std::cout << "\": [ ]," << std::endl;
                    else {
                        std::cout << "\": [" << std::endl;
                        for (auto const &e : _data)
                            e->print(base_indent + indent_size);
                        std::cout << std::string(base_indent, ' ') << "]," << std::endl;
                    }
                }

                Property const &operator=(std::vector<std::shared_ptr<Object>> const &newData) override { setData(newData); return (*this); };
                Property const &operator+=(std::shared_ptr<Object> const &newData) { addData(newData); return (*this); };
                Property const &operator+=(std::vector<std::shared_ptr<Object>> const &newData) { addData(newData); return (*this); };
                std::shared_ptr<Object> const &operator[](std::size_t const &i) { return (getData(i)); };

            private:
                std::vector<std::shared_ptr<Object>> _data;
        };

        template <class T>
        class Array<std::shared_ptr<Array<T>>> : public Property {
            public:
                Array(std::string const &name, std::vector<std::shared_ptr<Array<T>>> const &v = { }) :
                    Property(name, Type::_array, Type::_array), _data(v) { };
                ~Array() = default;

                std::size_t const getSize() const { return _data.size(); };
                std::shared_ptr<Array<T>> const &getData(std::size_t i) const { return _data[i]; };
                void setData(std::vector<std::shared_ptr<Array<T>>> const &data) { _data = data; }

                void addData(std::shared_ptr<Array<T>> const &data) { _data.push_back(data); }
                void addData(std::vector<std::shared_ptr<Array<T>>> const &data) { _data.insert(_data.end(), data.begin(), data.end()); }

                void eraseValue(std::size_t const &i) { _data.erase(_data.begin() + i); }

                void dump(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    std::cout << std::string(base_indent, ' ') << '"' << _name << "\": [" << std::endl;
                    for (auto const &e : _data)
                        e->dump(base_indent + indent_size);
                    std::cout << std::string(base_indent, ' ') << "]," << std::endl;
                }

                void print(std::size_t base_indent = 0, std::size_t indent_size = 4) const
                {
                    std::cout << std::string(base_indent, ' ') << '"' << _name;
                    if (_data.empty())
                        std::cout << "\": [ ]," << std::endl;
                    else {
                        std::cout << "\": [" << std::endl;
                        for (auto const &e : _data)
                            e->print(base_indent + indent_size);
                        std::cout << std::string(base_indent, ' ') << "]," << std::endl;
                    }
                }

                Property const &operator=(std::vector<std::shared_ptr<Array<T>>> const &newData) override { setData(newData); return (*this); };
                Property const &operator+=(std::shared_ptr<Array<T>> const &newData) { addData(newData); return (*this); };
                Property const &operator+=(std::vector<std::shared_ptr<Array<T>>> const &newData) { addData(newData); return (*this); };
                std::shared_ptr<Array<T>> const &operator[](std::size_t const &i) { return (getData(i)); };

            private:
                std::vector<std::shared_ptr<Array<T>>> _data;
        };

        static std::shared_ptr<Property> const operator+=(std::shared_ptr<Array<int>> const &ptr, int const &newData) { ptr->addData(newData); return (ptr); };
        static std::shared_ptr<Property> const operator+=(std::shared_ptr<Array<double>> const &ptr, double const &newData) { ptr->addData(newData); return (ptr); };
        static std::shared_ptr<Property> const operator+=(std::shared_ptr<Array<std::string>> const &ptr, std::string const &newData) { ptr->addData(newData); return (ptr); };
        static std::shared_ptr<Property> const operator+=(std::shared_ptr<Array<std::shared_ptr<Object>>> const &ptr, std::shared_ptr<Object> const &newData) { ptr->addData(newData); return (ptr); };

        static std::shared_ptr<Property> const operator+=(std::shared_ptr<Array<int>> const &ptr, std::vector<int> const &newData) { ptr->addData(newData); return (ptr); };
        static std::shared_ptr<Property> const operator+=(std::shared_ptr<Array<double>> const &ptr, std::vector<double> const &newData) { ptr->addData(newData); return (ptr); };
        static std::shared_ptr<Property> const operator+=(std::shared_ptr<Array<std::string>> const &ptr, std::vector<std::string> const &newData) { ptr->addData(newData); return (ptr); };
        static std::shared_ptr<Property> const operator+=(std::shared_ptr<Array<std::shared_ptr<Object>>> const &ptr, std::vector<std::shared_ptr<Object>> const &newData) { ptr->addData(newData); return (ptr); };

        template <class T>
        static std::shared_ptr<Array<T>> createArray(std::string const &name, std::vector<T> const &data = { })
        {
            return (std::make_shared<Array<T>>(name, data));
        }
    }
}

#endif /* !ARRAY_HPP_ */

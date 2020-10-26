/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <fstream>

#include "Error.hpp"
#include "String.hpp"
#include "Object.hpp"

namespace Babel {
    namespace Json {
        class Parser {
            static std::string stripFile(std::string const &filename)
            {
                std::ifstream infile(filename);
                std::string tmp;
                std::string input;
                std::string output;
                bool inQuote = false;

                while (std::getline(infile, tmp)) input += tmp;

                for(std::size_t i = 0; i < input.size(); ++i) {
                    if (input[i] == '"')
                        inQuote = !inQuote;
                    if ((input[i] != ' ' && input[i] != '\t') || inQuote)
                        output += input[i];
                }
                return (output);
            }

            static std::string findMatchingChar(std::string const &str, std::string const &c, std::string const &not_c)
            {
                std::size_t cmp = 1;
                std::size_t i = 1;

                for (; i < str.length() && cmp; ++i) {
                    if (c == not_c && c.find(str[i]) != std::string::npos) return (str.substr(1, i - 1));
                    if (c.find(str[i]) != std::string::npos) ++cmp;
                    if (not_c.find(str[i]) != std::string::npos) --cmp;
                }
                return (str.substr(1, i - 2));
            }

            static std::shared_ptr<Property> readValue(std::string const &name, std::string const &str)
            {
                std::string value = str.substr(0, _find_first_of(str, ",}]"));

                if (value[0] == '"' && value[value.length() - 1] == '"')
                    return (createValue(name, value.substr(1, value.length() - 2)));
                else if (value.find_first_not_of("0123456789-.") != std::string::npos)
                    throw ParserError("Invalid Property value: " + value);
                else if (value.find('.') != std::string::npos)
                    return (createValue(name, std::stod(value)));
                return (createValue(name, std::stoi(value)));
            }

            static std::shared_ptr<Object> readObject(std::string const &name, std::string const &str, std::shared_ptr<Object> const &obj)
            {
                auto ptr = createObject(name);
                read(str, ptr);
                return (ptr);
            }

            static std::vector<std::string> readStringArray(std::string str)
            {
                std::vector<std::string> v;
                std::string value;

                while (str != "") {
                    if (str[0] == ',') str = str.substr(1);
                    value = findMatchingChar(str, "\"", "\"");
                    v.push_back(value);
                    str = str.substr(value.length() + 2);
                }
                return (v);
            }

            static std::vector<int> readIntArray(std::string str)
            {
                std::vector<int> v;
                std::size_t del;

                while (str != "") {
                    if (str[0] == ',') str = str.substr(1);
                    del = str.find(',');
                    if (del == std::string::npos) {
                        v.push_back(std::stoi(str));
                        str = "";
                    } else {
                        v.push_back(std::stoi(str.substr(0, del)));
                        str = str.substr(del);
                    }
                }
                return (v);
            }

            static std::vector<double> readDoubleArray(std::string str)
            {
                std::vector<double> v;
                std::size_t del;

                while (str != "") {
                    if (str[0] == ',') str = str.substr(1);
                    del = str.find(',');
                    if (del == std::string::npos) {
                        v.push_back(std::stod(str));
                        str = "";
                    } else {
                        v.push_back(std::stod(str.substr(0, del)));
                        str = str.substr(del);
                    }
                }
                return (v);
            }

            static std::vector<std::shared_ptr<Object>> readObjectArray(std::string str)
            {
                std::vector<std::shared_ptr<Object>> v;
                std::string obj_str;

                while (str != "") {
                    auto obj = createObject("");
                    if (str[0] == ',') str = str.substr(1);
                    obj_str = findMatchingChar(str, "{", "}");
                    read(obj_str, obj);
                    v.push_back(obj);
                    str = str.substr(obj_str.length() + 2);
                }
                return (v);
            }

            static std::vector<std::shared_ptr<Property>> readArrayOfArray(std::string str)
            {
                std::vector<std::shared_ptr<Property>> v;
                std::string arr;

                while (str != "") {
                    if (str[0] == ',') str = str.substr(1);
                    arr = findMatchingChar(str, "[", "]");
                    v.push_back(readArray("", arr));
                    str = str.substr(arr.length());
                }
                return (v);
            }

            static std::shared_ptr<Property> readArray(std::string const &name, std::string const &str)
            {
                if (str[0] == '{' && str[str.length() - 1] == '}')
                    return (createArray(name, readObjectArray(str)));
                // else if (value[0] == '[' && value[value.length() - 1] == ']')
                //     return (createArray(name, readArrayOfArray(str)));

                std::size_t del = str.find(',');
                std::string value;

                if (del == std::string::npos) value = str;
                else value = str.substr(0, del);
                if (value[0] == '"' && value[value.length() - 1] == '"')
                    return (createArray(name, readStringArray(str)));
                else if (value.find_first_not_of("0123456789-.") != std::string::npos)
                    throw ParserError("Invalid Property value in Array: " + value);
                else if (value.find('.') != std::string::npos)
                    return (createArray(name, readDoubleArray(str)));
                return (createArray(name, readIntArray(str)));
            }

            static void read(std::string file, std::shared_ptr<Object> const &obj)
            {
                std::string propertyName;
                std::size_t eop;

                if (file[0] == ',') file = file.substr(1);
                if (file[0] == ']' || file[0] == '}' || file == "") return;

                eop = file.find('"', 1);
                if (file[0] != '"' || eop == std::string::npos)
                    throw ParserError("Invalid syntax on Property declaration");
                propertyName = file.substr(1, eop - 1);
                if (file[eop + 1] != ':')
                    throw ParserError("Missing \":\" after Property named '" + propertyName + "'");

                if (file[eop + 2] == '[') {
                    obj->addPropertyToObject(readArray(propertyName, findMatchingChar(file.substr(eop + 2), "[", "]")));
                    read(file.substr(findMatchingChar(file.substr(eop + 2), "[", "]").length() + 5 + propertyName.length()), obj);
                } else if (file[eop + 2] == '{') {
                    obj->addPropertyToObject(readObject(propertyName, findMatchingChar(file.substr(eop + 2), "{", "}"), obj));
                    read(file.substr(findMatchingChar(file.substr(eop + 2), "{", "}").length() + 5 + propertyName.length()), obj);
                } else if (std::string("0123456789-\"").find(file[eop + 2]) != std::string::npos) {
                    std::size_t del = _find_first_of(file, ",}]", eop + 2);

                    obj->addPropertyToObject(readValue(propertyName, file.substr(eop + 2)));
                    if (del == std::string::npos) return;
                    read(file.substr(eop + 2 + del), obj);
                } else
                    throw ParserError("Unknown Property type");
            }

            public:
                static void parse(std::string const &filename, std::shared_ptr<Object> const &obj)
                {
                    std::string file = stripFile(filename);
                    read(file.substr(1, file.length() - 2), obj);
                }
        };
    }
}

#endif /* !PARSER_HPP_ */

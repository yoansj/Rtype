/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** TagComponent
*/

#ifndef TAGCOMPONENT_HPP_
#define TAGCOMPONENT_HPP_

#include "Component.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace Client {
    namespace Components {
        class TagComponent : public Client::Components::Component {
            public:
                TagComponent(std::vector<std::string> tagList) : Client::Components::Component("Tag"), _tagList(tagList) {};
                ~TagComponent();

                std::vector<std::string> _tagList;
            protected:
            private:
        };
    }

}

#endif /* !TAGCOMPONENT_HPP_ */

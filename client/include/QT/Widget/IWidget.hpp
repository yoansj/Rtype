/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** IWidget
*/

#ifndef IWidget_HPP_
#define IWidget_HPP_

#include <QMainWindow>
#include <QDebug>
#include <QIcon>
#include <QListWidget>
#include <QSize>
#include <map>

namespace client {
    static std::map<int, std::string> _profilePhoto{
        std::make_pair(0, "../client/assets/image/marioBorder.png"),
        std::make_pair(1, "../client/assets/image/veigoBorder.png"),
        std::make_pair(2, "../client/assets/image/linkBorder.png"),
        std::make_pair(3, "../client/assets/image/sonicBorder.png"),
        std::make_pair(4, "../client/assets/image/steveBorder.png")
    };

    class IWidget : public QWidget {
        public:
            virtual ~IWidget() = default;

            virtual bool isActive() const = 0;
            virtual void setActive(bool const &) = 0;
    };
}

#endif /* !IWidget_HPP_ */

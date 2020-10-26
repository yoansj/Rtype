/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Root
*/

#ifndef ROOT_HPP_
#define ROOT_HPP_

#include <QApplication>
#include <QFontDatabase>

#include "WidgetManager.hpp"
#include "LoginPage.hpp"

namespace client {
    class Root {
        public:
            Root(int &argc, char **argv);
            ~Root();

            int start();

        private:
            QApplication _app;
            WidgetManager &_wm;
    };
}

#endif /* !ROOT_HPP_ */

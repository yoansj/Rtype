/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** Root
*/

#include "Root.hpp"

namespace client {
    Root::Root(int &argc, char **argv) :
        _app(argc, argv),
        _wm(WidgetManager::Get())
    {
        QApplication::setFont(QFontDatabase::systemFont(
            (QFontDatabase::SystemFont)QFontDatabase::addApplicationFont
            ("client/assets/Roboto-Black.ttf")));
        QFontDatabase::removeAllApplicationFonts();
    }

    int Root::start()
    {
        _wm.show();
        _wm.loadWidget<LoginPage>();
        return (_app.exec());
    }

    Root::~Root()
    { }
}


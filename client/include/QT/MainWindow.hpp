/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** MainWindow
*/

#ifndef MainWindow_HPP_
#define MainWindow_HPP_

#include <QMainWindow>
#include <QDebug>

namespace client {
    class MainWindow : public QMainWindow {
        Q_OBJECT
        public:
            MainWindow();
            ~MainWindow() = default;
    };
}

#endif /* !MainWindow_HPP_ */

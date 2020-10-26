/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** MainWindow
*/

#include "MainWindow.hpp"

client::MainWindow::MainWindow() : QMainWindow(nullptr)
{
    this->setFixedSize(1500, 800);
    this->setWindowTitle("Babel");
    this->setStyleSheet("background-color: rgb(204,255,255);");
}

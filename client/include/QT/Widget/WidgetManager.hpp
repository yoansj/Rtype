/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** WidgetManager
*/

#ifndef WIDGETMANAGER_HPP_
#define WIDGETMANAGER_HPP_

#include <map>
#include "NetworkManager.hpp"
#include "IWidget.hpp"
#include "MainWindow.hpp"

namespace client {
    class WidgetManager {
        public:
            static WidgetManager &Get() { static WidgetManager i; return i; };

            template <class T>
            void loadWidget()
            {
                _mainWindow.setCentralWidget(new T);
            }

            MainWindow const &getMainWindow() const { return _mainWindow; };
            Babel::Cache::Cache &getCache() { return _cache; };

            void show() { _mainWindow.show(); };

            Babel::NetworkManager &getNetworkManager() { return _nm; };

        private:
            MainWindow _mainWindow;
            Babel::NetworkManager _nm;
            Babel::Cache::Cache &_cache;

        private:
            WidgetManager() : _cache(Babel::Cache::Cache::Get()) { };
            ~WidgetManager() = default;

            WidgetManager(WidgetManager &&) = delete;
            WidgetManager(WidgetManager const &) = delete;
            WidgetManager &operator=(WidgetManager const &) = delete;
    };
}

#endif /* !WIDGETMANAGER_HPP_ */

/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** ChangeProfilPage
*/

#ifndef CHANGEPROFILPAGE_HPP_
#define CHANGEPROFILPAGE_HPP_

#include "WidgetManager.hpp"
#include "IWidget.hpp"
#include "UserPage.hpp"
#include <map>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class ChangeProfilPage; }
QT_END_NAMESPACE

namespace client {
    class ChangeProfilPage : public IWidget {
        Q_OBJECT
        public:
            ChangeProfilPage(QWidget *parent = 0);
            ~ChangeProfilPage();

            bool isActive() const { return _isActive; }
            void setActive(bool const &b) { _isActive = b; }

        private slots:
            void returnInMenu();
            void changeImage();
            void saveChanges();

        private:
            std::shared_ptr<Ui::ChangeProfilPage> ui;
            WidgetManager &_wm;
            bool _isActive;
    };
}

#endif /* !CHANGEPROFILPAGE_HPP_ */

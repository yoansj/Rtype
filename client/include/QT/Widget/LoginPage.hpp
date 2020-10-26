/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** LoginPage
*/

#ifndef LOGINPAGE_HPP_
#define LOGINPAGE_HPP_

#include "WidgetManager.hpp"
#include "IWidget.hpp"
#include "CreateAccountPage.hpp"
#include "UserPage.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginPage; }
QT_END_NAMESPACE

namespace client {
    class LoginPage : public IWidget {
        Q_OBJECT
        public:
            LoginPage(QWidget *parent = 0);
            ~LoginPage();

            bool isActive() const { return _isActive; }
            void setActive(bool const &b) { _isActive = b; }

        private slots:
            void login();
            void loginResponse(bool b);
            void createAcc();

        private:
            std::shared_ptr<Ui::LoginPage> ui;
            WidgetManager &_wm;
            bool _isActive;
    };
}

#endif /* !LOGINPAGE_HPP_ */

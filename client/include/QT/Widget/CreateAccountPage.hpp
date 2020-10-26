/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** CreateAccountPage
*/

#ifndef CREATEACCOUNTPAGE_HPP_
#define CREATEACCOUNTPAGE_HPP_

#include "WidgetManager.hpp"
#include "IWidget.hpp"
#include "LoginPage.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CreateAccountPage; }
QT_END_NAMESPACE

namespace client {
    class CreateAccountPage : public IWidget {
        Q_OBJECT
        public:
            CreateAccountPage(QWidget *parent = 0);
            ~CreateAccountPage();

            bool isActive() const { return _isActive; }
            void setActive(bool const &b) { _isActive = b; }

        private slots:
            void verifyAccount();
            void returnInLogin();
            void createAccResponse(bool b);

        private:
            bool checkQlineContent(QString str);

            std::shared_ptr<Ui::CreateAccountPage> ui;
            WidgetManager &_wm;
            bool _isActive;
    };
}

#endif /* !CreateAccountPage_HPP_ */

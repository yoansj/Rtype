/*
** EPITECH PROJECT, 2020
** client
** File description:
** UserPage
*/

#ifndef USERPAGE_HPP_
#define USERPAGE_HPP_

#include "WidgetManager.hpp"
#include "IWidget.hpp"
#include "LoginPage.hpp"
#include "ChangeProfilPage.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class UserPage; }
QT_END_NAMESPACE


namespace client {
    class UserPage : public IWidget {
        Q_OBJECT
        public:
            UserPage(QWidget *parent = 0);
            ~UserPage();

            bool isActive() const { return _isActive; }
            void setActive(bool const &b) { _isActive = b; }

        private slots:
            void disconnect();
            void displayFriend();
            void editProfile();
            void displayGroup();
            void addFriend();
            void tabChanged();
            void createGroup();
            void addToGroup();
            void changeFriendBar();
            void changeInviteToGroupBar();
            void enterCall();

            void addFriendResponse(bool b);

        private:
            std::shared_ptr<Ui::UserPage> ui;
            WidgetManager &_wm;
            bool _isActive;

        private:
            void buildContactList();
            std::size_t isReceivingCallNotif() const;
    };
}

#endif /* !USERPAGE_HPP_ */

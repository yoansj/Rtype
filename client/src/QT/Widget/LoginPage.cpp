/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** LoginPage
*/

#include "LoginPage.hpp"
#include "ui_LoginPage.h"

client::LoginPage::LoginPage(QWidget *parent) :
    ui(std::make_shared<Ui::LoginPage>()),
    _wm(WidgetManager::Get()), _isActive(true)
{
    ui->setupUi(this);
    QPixmap pix("../client/assets/image/babel.png");
    ui->label->setPixmap(pix);
    connect(ui->create, SIGNAL(clicked(bool)), this, SLOT(createAcc()));
    connect(ui->login, SIGNAL(clicked(bool)), this, SLOT(login()));
    connect(&_wm.getNetworkManager(), SIGNAL(authentificationFailed(bool)), this, SLOT(loginResponse(bool)));
    ui->_errorTxt->hide();

}

client::LoginPage::~LoginPage()
{ }

void client::LoginPage::login()
{
    if (!_isActive) return;

    auto us = QString(ui->username->text()).toUtf8();
    auto pw = QString(ui->password->text()).toUtf8();
    // qDebug() << "us:" << us;
    // qDebug() << "pw:" << pw;

    if (us != "" && pw != "")
        _wm.getNetworkManager().login(us.constData(), pw.constData());
}

void client::LoginPage::createAcc()
{
    setActive(false);
    _wm.loadWidget<CreateAccountPage>();
}

void client::LoginPage::loginResponse(bool b)
{
    if (!_isActive) return;

    if (b)
        ui->_errorTxt->setVisible(true);
    else {
        setActive(false);
        _wm.loadWidget<UserPage>();
    }
}

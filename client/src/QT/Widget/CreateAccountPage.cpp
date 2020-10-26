/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** CreateAccountPage
*/

#include "CreateAccountPage.hpp"
#include "ui_CreateAccountPage.h"

client::CreateAccountPage::CreateAccountPage(QWidget *parent) :
    ui(std::make_shared<Ui::CreateAccountPage>()),
    _wm(WidgetManager::Get()), _isActive(true)
{
    ui->setupUi(this);
    connect(ui->Create, SIGNAL(clicked(bool)), this, SLOT(verifyAccount()));
    QPixmap pix("../client/assets/image/arrow.png");
    ui->back->setIcon(QIcon(pix));
    ui->back->setIconSize(QSize(81, 81));
    connect(ui->back, SIGNAL(clicked(bool)), this, SLOT(returnInLogin()));
    connect(&_wm.getNetworkManager(), SIGNAL(pseudoAlreadyExist(bool)), this, SLOT(createAccResponse(bool)));
    ui->_errorTxt->hide();
}

client::CreateAccountPage::~CreateAccountPage()
{ }

void client::CreateAccountPage::verifyAccount()
{
    auto us = QString(ui->username->text()).toUtf8();
    auto pw = QString(ui->password->text()).toUtf8();

    if (us != "" && pw != "")
        _wm.getNetworkManager().createProfile(us.constData(), pw.constData());
}

void client::CreateAccountPage::createAccResponse(bool b)
{
    if (!_isActive) return;

    if (b)
        ui->_errorTxt->setVisible(true);
    else {
        setActive(false);
        _wm.getCache().__forceRebuild__();
        _wm.loadWidget<LoginPage>();
    }
}

void client::CreateAccountPage::returnInLogin()
{
    setActive(false);
    _wm.loadWidget<LoginPage>();
}

bool client::CreateAccountPage::checkQlineContent(QString str)
{
    QChar c = str.at(0);
    switch (c.unicode()) {
        case ' ':
            return (false);
            break;
        case '\\':
            return (false);
            break;
    }
    if (str.isEmpty())
        return (false);
    return (true);
}
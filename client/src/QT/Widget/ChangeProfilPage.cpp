/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** ChangeProfilPage
*/

#include "ChangeProfilPage.hpp"
#include "ui_ChangeProfilPage.h"

client::ChangeProfilPage::ChangeProfilPage(QWidget *parent) :
    ui(std::make_shared<Ui::ChangeProfilPage>()),
    _wm(WidgetManager::Get()), _isActive(true)
{
    ui->setupUi(this);
    QPixmap pix("../client/assets/image/arrow.png");
    ui->back->setIcon(QIcon(pix));
    ui->back->setIconSize(QSize(81, 81));
    for (int i = 0; i < 5; i++) {
        QListWidgetItem *item = new QListWidgetItem;
        std::string temp = _profilePhoto.find(i)->second;
        item->setIcon(QIcon(QString::fromUtf8(temp.c_str())));
        ui->imageList->addItem(item);
    }
    ui->imageList->setIconSize(QSize(100, 100));
    ui->imageList->setFlow(QListWidget::LeftToRight);
    ui->imageList->setWrapping(true);

    ui->_errorTxt->hide();

    connect(ui->back, SIGNAL(clicked(bool)), this, SLOT(returnInMenu()));
    connect(ui->saveChanges, SIGNAL(clicked(bool)), this, SLOT(saveChanges()));
    connect(ui->imageList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(changeImage()));

}

client::ChangeProfilPage::~ChangeProfilPage()
{ }

void client::ChangeProfilPage::returnInMenu()
{
    setActive(false);
    _wm.loadWidget<UserPage>();
}

void client::ChangeProfilPage::changeImage()
{
    qDebug() << ui->imageList->currentRow();
    // QPixmap pix(_image.find(ui->imageList->currentRow())->second);
    std::string temp = _profilePhoto.find(ui->imageList->currentRow())->second;
    QPixmap pix(QString::fromUtf8(temp.c_str()));
    ui->profileIcon->setPixmap(pix);
}

void client::ChangeProfilPage::saveChanges()
{
    // ui->_errorTxt->setVisible(true);
    // qDebug() << ui->imageList->currentRow();
    /*_wm.getNetworkManager().ammendProfile(QString(ui->username->text()).toUtf8().constData(),
                                        QString(ui->username->text()).toUtf8().constData(),
                                        ui->imageList->currentRow()); */
}

/*
** EPITECH PROJECT, 2020
** client
** File description:
** UserPage
*/

#include "UserPage.hpp"
#include "ui_UserPage.h"

client::UserPage::UserPage(QWidget *parent) :
    ui(std::make_shared<Ui::UserPage>()),
    _wm(WidgetManager::Get()), _isActive(true)
{
    ui->setupUi(this);
    ui->username->setText(_wm.getCache().getValue<std::string>("pseudo", "profil")->getData().data());
    ui->profileIcon->setPixmap(QPixmap(_profilePhoto[_wm.getCache().getValue<int>("pp", "profil")->getData()].data()));
    ui->enterCall->setIcon(QIcon(QPixmap("../client/assets/image/acceptCall.png")));
    ui->enterCall->setIconSize(QSize(40, 40));
    ui->quitCall->setIcon(QIcon(QPixmap("../client/assets/image/quitCall.png")));
    ui->quitCall->setIconSize(QSize(40, 40));
    ui->disconnect->setIcon(QIcon(QPixmap("../client/assets/image/logout.png")));
    ui->disconnect->setIconSize(QSize(61,51));

    buildContactList();
    for (int i = 0; i < 10; i++) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon("../client/assets/image/group.png"));
        item->setText("User " + QString::number(i));
        ui->groupList->addItem(item);
    }
    for (int i = 0; i < 2; i++) {
        QListWidgetItem *item = new QListWidgetItem;
        QIcon *test = new QIcon;
        item->setIcon(QIcon("../client/assets/image/marioBorder.png"));
        item->setText("User " + QString::number(i));

        ui->callList->addItem(item);
    }


    ui->nameFriend->setStyleSheet("font: 18pt;");
    ui->_nameFriend->hide();
    ui->_imageFriend->hide();
    ui->_statut->hide();
    ui->_groupList->hide();
    ui->_invitGroup->hide();
    ui->_enterCall->hide();
    ui->_quitCall->hide();

    connect(ui->disconnect, SIGNAL(clicked(bool)), this, SLOT(disconnect()));
    connect(ui->editProfile, SIGNAL(clicked(bool)), this, SLOT(editProfile()));
    connect(ui->userList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(displayFriend()));
    connect(ui->groupList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(displayGroup()));
    connect(ui->addFriend, SIGNAL(clicked(bool)), this, SLOT(addFriend()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged()));
    connect(ui->createGroup, SIGNAL(clicked(bool)), this, SLOT(createGroup()));
    connect(ui->addToGroup, SIGNAL(clicked(bool)), this, SLOT(addToGroup()));
    connect(ui->friendBar, SIGNAL(textChanged(const QString &)), this, SLOT(changeFriendBar()));
    connect(ui->inviteBar, SIGNAL(textChanged(const QString &)), this, SLOT(changeInviteToGroupBar()));
    connect(ui->enterCall, SIGNAL(clicked(bool)), this, SLOT(enterCall()));

    connect(&_wm.getNetworkManager(), SIGNAL(profilNotAdded(bool)), this, SLOT(addFriendResponse(bool)));
}

client::UserPage::~UserPage()
{ }


void client::UserPage::buildContactList()
{
    auto &cache = _wm.getCache();
    cache.print();
    auto contactList = cache.getArray<std::shared_ptr<Babel::Json::Object>>("contact_list");

    ui->userList->clear();
    for (std::size_t i = 0; i < contactList->getSize(); ++i) {
        auto pseudo = std::dynamic_pointer_cast<Babel::Json::Value<std::string>>((*contactList)[i]->getPropertyFromObject("pseudo"))->getData();
        if (pseudo == "") continue;
        auto pp = std::dynamic_pointer_cast<Babel::Json::Value<int>>((*contactList)[i]->getPropertyFromObject("pp"))->getData();
        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon(_profilePhoto[pp].data()));
        item->setText(pseudo.data());
        ui->userList->addItem(item);
    }
}

void client::UserPage::disconnect()
{
    _wm.getCache().__forceRebuild__();
    _wm.loadWidget<LoginPage>();
}

void client::UserPage::displayFriend()
{
    ui->_groupList->hide();
    ui->_invitGroup->hide();

    auto arr = _wm.getCache().getArray<std::shared_ptr<Babel::Json::Object>>("contact_list");

    // ui->imageFriend->setPixmap(QPixmap(_profilePhoto[std::dynamic_pointer_cast<Babel::Json::Value<int>>((*arr)[ui->userList->currentRow()]->getPropertyFromObject("pp"))->getData()].data()));
    ui->imageFriend->setPixmap(QPixmap(_profilePhoto[0].data()));
    ui->_nameFriend->setVisible(true);
    ui->_imageFriend->setVisible(true);
    ui->_enterCall->setVisible(true);
    ui->_quitCall->setVisible(true);
    ui->_statut->setVisible(true);
    if (std::dynamic_pointer_cast<Babel::Json::Value<int>>((*arr)[ui->userList->currentRow() + 1]->getPropertyFromObject("status"))->getData() == 0)
        ui->statutIcon->setPixmap(QPixmap("../client/assets/image/pasco.png"));
    else
        ui->statutIcon->setPixmap(QPixmap("../client/assets/image/co.png"));
    ui->nameFriend->setText(std::dynamic_pointer_cast<Babel::Json::Value<std::string>>((*arr)[ui->userList->currentRow() + 1]->getPropertyFromObject("pseudo"))->getData().data());

}

void client::UserPage::displayGroup()
{
    ui->_statut->hide();
    qDebug() << "lol";
    QPixmap pix("../client/assets/image/group.png");
    ui->imageFriend->setPixmap(pix);
    qDebug() << ui->userList->currentRow();
    ui->_nameFriend->setVisible(true);
    ui->nameFriend->setText("Groupe ultime de la mort qui tue");
    ui->_imageFriend->setVisible(true);
    ui->_enterCall->setVisible(true);
    ui->_quitCall->setVisible(true);
    ui->_groupList->setVisible(true);
    ui->_invitGroup->setVisible(true);
}

void client::UserPage::editProfile()
{
    setActive(false);
    _wm.loadWidget<ChangeProfilPage>();
}

void client::UserPage::addFriend()
{
    auto pseudo = QString(ui->friendBar->text()).toUtf8();

    if (pseudo != "")
        _wm.getNetworkManager().addContactSender(pseudo.constData());
}

void client::UserPage::addFriendResponse(bool b)
{
    if (b) {
        ui->friendBar->setStyleSheet("background-color: rgb(255, 102, 102)");
        ui->friendBar->setPlaceholderText("Error");
        ui->friendBar->clear();
    } else {
        buildContactList();
    }
}

void client::UserPage::tabChanged()
{
    ui->userList->setCurrentRow(-1);
    ui->groupList->setCurrentRow(-1);
}

void client::UserPage::createGroup()
{
    if (ui->groupBar->text() == "") {
        return;
    }

    // _wm.getNetworkManager().createGroup(QString(ui->groupBar->text()).toUtf8().constData());
}

void client::UserPage::addToGroup()
{
    if (ui->inviteBar->text() == "") {
        ui->inviteBar->setStyleSheet("background-color: rgb(255, 102, 102)");
        ui->inviteBar->setPlaceholderText("Error");
        ui->inviteBar->clear();
        return;
    }
    // _wm.getNetworkManager().addContactToGroup(ID_DU_GROUPE XD, QString(ui->inviteBar->text()).toUtf8().constData());
}

void client::UserPage::changeFriendBar()
{
    ui->friendBar->setPlaceholderText("Search");
    ui->friendBar->setStyleSheet("background-color: rgb(238, 238, 236);");
}

void client::UserPage::changeInviteToGroupBar()
{
    ui->inviteBar->setPlaceholderText("Search");
    ui->inviteBar->setStyleSheet("background-color: rgb(238, 238, 236);");
}

std::size_t client::UserPage::isReceivingCallNotif() const
{
    // ui->userList->item(0)->setText("Userrrrrrrr 0 is calling you !");
    // ui->userList->item(0)->setIcon(QIcon("../client/assets/image/call.png"));
    auto ctcArr = _wm.getCache().getArray<std::shared_ptr<Babel::Json::Object>>("contact_list");

    for (std::size_t i = 1; i < ctcArr->getSize(); ++i) {
        auto value = std::dynamic_pointer_cast<Babel::Json::Value<std::string>>((*ctcArr)[i]->getPropertyFromObject("id_group"));

        if (value && value->getData() != "0")
            return (i);
    }
    return (0);
}

void client::UserPage::enterCall()
{
    if (ui->_statut->isVisible()) {
        auto ctcArr = _wm.getCache().getArray<std::shared_ptr<Babel::Json::Object>>("contact_list");
        std::string myPseudo = _wm.getCache().getValue<std::string>("pseudo", "profil")->getData();
        std::size_t callIndex = isReceivingCallNotif();

        if (callIndex) {
            std::string id = std::dynamic_pointer_cast<Babel::Json::Value<std::string>>((*ctcArr)[callIndex]->getPropertyFromObject("id_group"))->getData();

            _wm.getNetworkManager().acceptCall(myPseudo, id);
        } else {
            auto user = (*ctcArr)[ui->userList->currentRow() + 1];
            auto userPseudo = std::dynamic_pointer_cast<Babel::Json::Value<std::string>>(user->getPropertyFromObject("pseudo"))->getData();

            _wm.getNetworkManager().notifCallSender("ID TEST", { myPseudo, userPseudo }, _wm.getNetworkManager().getUdpAddress(), _wm.getNetworkManager().getUdpPort());
        }
    } else {

    }
}
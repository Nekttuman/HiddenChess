#include "HiddenChess.h"

HiddenChess::HiddenChess(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.mainMenuWidget->move(0, 0);
    ui.mainMenuWidget->setFixedSize(this->size());
    
    ui.joiningWidget->hide();
    ui.joiningWidget->move(0, 0);
    ui.joiningWidget->setFixedSize(this->size());

    ui.roomCreationWidget->hide();
    ui.roomCreationWidget->move(0, 0);
    ui.roomCreationWidget->setFixedSize(this->size());

    ui.gameWidget->hide();
    ui.gameWidget->move(0, 0);
    ui.gameWidget->setFixedSize(this->size());

    client = new Client(this);
    

    
    connect(ui.mainMenuWidget, &MainMenu::createRoomBtn_signal, this, &HiddenChess::showCreateRoomWidget_slot);
    connect(ui.mainMenuWidget, &MainMenu::joinRoomBtn_signal, this, &HiddenChess::showJoiningWidget_slot);
    connect(ui.mainMenuWidget, &MainMenu::exitBtn_signal, this, &HiddenChess::exit_slot);
    connect(ui.roomCreationWidget, &RoomCreationWidget::backToMenu_signal,
        this, &HiddenChess::showMainMenu_slot);
    
    connect(ui.roomCreationWidget, &RoomCreationWidget::createRoom_signal,
        client, [&]() {client->tryCreateRoom(
            ui.roomCreationWidget->getRoomName(),
            ui.roomCreationWidget->getPswd()
        ); });


    connect(ui.joiningWidget, &JoiningWidget::backToMenu_signal,
        this, &HiddenChess::showMainMenu_slot);
    connect(ui.joiningWidget, &JoiningWidget::startGame_signal,
        this, &HiddenChess::showGameWidget_slot);

    connect(ui.gameWidget, &GameWidget::backToMenu_signal,
        this, &HiddenChess::showMainMenu_slot);

    connect(ui.mainMenuWidget, &MainMenu::createRoomBtn_signal, client, &Client::connectToHost_slot);
    connect(client, &Client::connectionErr_signal, this, &HiddenChess::disableGame_slot);
    connect(client, &Client::connectionErr_signal, this, [&]() {has_connection = false; });


    connect(client, &Client::connected_signal, this, [&]() {has_connection = true; });
    connect(client, &Client::connected_signal, this, &HiddenChess::showConnectedMessage_slot);
    
    connect(ui.roomCreationWidget, &RoomCreationWidget::fieldsCorrect_signal,
        ui.roomCreationWidget, &RoomCreationWidget::allowRoomCreation_slot);
    connect(ui.roomCreationWidget, &RoomCreationWidget::checkRoomNameUniquness_signal,
        client, &Client::checkRoomNameUniq_slot);
    connect(client, &Client::roomNameUniqConfirmed_signal, ui.roomCreationWidget,
        &RoomCreationWidget::roomNameUniqConfirmed_slot);
    connect(client, &Client::roomNameUniqNotConfirmed_signal, ui.roomCreationWidget,
        &RoomCreationWidget::roomNameUniqNotConfirmed_slot);

}

HiddenChess::~HiddenChess()
{}

#include "HiddenChess.h"

HiddenChess::HiddenChess(QWidget *parent)
        : QMainWindow(parent) {
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


    connect(ui.mainMenuWidget, &MainMenu::createRoomBtn_signal, client, &Client::connectToHost_slot);
    connect(ui.mainMenuWidget, &MainMenu::joinRoomBtn_signal, client, &Client::connectToHost_slot);
    connect(ui.mainMenuWidget, &MainMenu::createRoomBtn_signal, this, &HiddenChess::showCreateRoomWidget_slot);
    connect(ui.mainMenuWidget, &MainMenu::joinRoomBtn_signal, this, &HiddenChess::showJoiningWidget_slot);
    connect(ui.mainMenuWidget, &MainMenu::exitBtn_signal, this, &HiddenChess::exit_slot);
    connect(ui.roomCreationWidget, &RoomCreationWidget::backToMenu_signal,
            this, &HiddenChess::showMainMenu_slot);

    //------------------------------- Room creation client-server connects
    connect(ui.roomCreationWidget, &RoomCreationWidget::createRoom_signal,
            client, [&]() {
                client->tryCreateRoom(
                        ui.roomCreationWidget->getRoomName(),
                        ui.roomCreationWidget->getPswd(),
                        ui.roomCreationWidget->getNick());
            });
    connect(client, &Client::roomCreated_signal, this, &HiddenChess::showGameWidget_slot);
    connect(client, &Client::roomCreated_signal, ui.gameWidget,
            [&]() { ui.gameWidget->setHostNick_slot(ui.roomCreationWidget->getNick()); });
    connect(client, &Client::roomCreated_signal, ui.gameWidget, &GameWidget::startGame_slot);
    connect(client, &Client::roomCreated_signal, this, [&]() { ui.roomCreationWidget->hide(); });
    connect(client, &Client::roomCreated_signal, this, [&]() { ui.roomCreationWidget->clearFields(); });

    //--------------------------------- Room joining client-server connects
    connect(ui.joiningWidget, &JoiningWidget::backToMenu_signal,
            this, &HiddenChess::showMainMenu_slot);
    connect(ui.joiningWidget, &JoiningWidget::tryJoining_signal,
            client, &Client::sendJoiningRequest_slot);
    connect(client, &Client::joinedToRoom, this, &HiddenChess::showGameWidget_slot);
    connect(client, &Client::joinedToRoom, this, [&]() { ui.joiningWidget->hide(); });
    connect(client, &Client::joinedToRoom, ui.gameWidget, &GameWidget::startGame_slot);
    connect(client, &Client::opponentNickRecieved_signal, ui.gameWidget, &GameWidget::setOpponentNick_slot);
    connect(client, &Client::joinedToRoom, ui.gameWidget,
            [&]() { ui.gameWidget->setHostNick_slot(ui.joiningWidget->getNick()); });
    connect(client, &Client::joinedToRoom, this, [&]() { ui.joiningWidget->clearFields(); });
    connect(client, &Client::joinedToRoom, this, [&]() { ui.errTextBrowser->clear(); });

    //---------------------------------
    connect(client, &Client::clientErr_signal, this, &HiddenChess::disableGame_slot);
    connect(client, &Client::clientErr_signal, this, [&]() { has_connection = false; });


    connect(client, &Client::connected_signal, this, [&]() { has_connection = true; });
    connect(client, &Client::connected_signal, this, &HiddenChess::showConnectedMessage_slot);

    connect(ui.roomCreationWidget, &RoomCreationWidget::checkRoomNameUniq_signal,
            client, &Client::checkRoomNameUniq_slot);
    connect(client, &Client::roomNameUniqConfirmed_signal, ui.roomCreationWidget,
            &RoomCreationWidget::roomNameUniqConfirmed_slot);
    connect(client, &Client::roomNameUniqNotConfirmed_signal, ui.roomCreationWidget,
            &RoomCreationWidget::roomNameUniqNotConfirmed_slot);


    connect(ui.gameWidget, &GameWidget::backToMenu_signal,
            this, &HiddenChess::showMainMenu_slot);

}

HiddenChess::~HiddenChess() {}

void HiddenChess::disableGame_slot(QString err) {
    ui.roomCreationWidget->disableCreateRoomBtn();
    qDebug() << "disableGame slot called";
    ui.errTextBrowser->setText(err);
    ui.errTextBrowser->setStyleSheet(ui.errTextBrowser->styleSheet() + "\ncolor:red;");
}

void HiddenChess::showConnectedMessage_slot() {
    ui.errTextBrowser->setText("Connected");
    ui.errTextBrowser->setStyleSheet(ui.errTextBrowser->styleSheet() + "color:green;");
}

void HiddenChess::paintEvent(QPaintEvent) {

    ui.mainMenuWidget->setFixedSize(this->size());
    ui.joiningWidget->setFixedSize(this->size());
    ui.roomCreationWidget->setFixedSize(this->size());
    ui.gameWidget->setFixedSize(this->size());
}

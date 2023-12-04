#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setGUI();
    client = new Client(this);

// set global signal-slot connections
    splashScreen_connections();
    logging_connections();
    mainMenu_connections();
    roomCreation_connections();
    roomsList_connections();
    roomJoining_connections();
    gameConfirmation_connections();
    gameWidget_connections();
}

void MainWindow::setGUI() {
    ui.setupUi(this);

    ui.mainMenuWidget->move(0, 0);
    ui.mainMenuWidget->setFixedSize(this->size());
    ui.mainMenuWidget->hide();

    ui.joiningWidget->hide();
    ui.joiningWidget->move(0, 0);
    ui.joiningWidget->setFixedSize(this->size());

    ui.roomCreationWidget->hide();
    ui.roomCreationWidget->move(0, 0);
    ui.roomCreationWidget->setFixedSize(this->size());

    ui.gameWidget->hide();
    ui.gameWidget->move(0, 0);
    ui.gameWidget->setFixedSize(this->size() - QSize(0, 30));

    ui.roomsListWidget->hide();
    ui.roomsListWidget->move(0, 0);
    ui.roomsListWidget->setFixedSize(this->size());

    ui.loginWidget->move(0, 0);
    ui.loginWidget->setFixedSize(this->size());
    ui.loginWidget->hide();

    ui.roomsListWidget->move(0, 0);
    ui.roomsListWidget->setFixedSize(this->size());
    ui.roomsListWidget->hide();

    ui.splashScreenWidget->move(0, 0);
    ui.splashScreenWidget->setFixedSize(this->size());
    ui.splashScreenWidget->show();

    ui.gameConfirmationWidget->move(0, 0);
    ui.gameConfirmationWidget->setFixedSize(this->size());
    ui.gameConfirmationWidget->hide();
}

MainWindow::~MainWindow() {}

//void MainWindow::disableGame_slot(QString err) {
//    ui.roomCreationWidget->disableCreateRoomBtn();
//    qDebug() << "MainWindow::disableGame_slot(QString err) slot called";
//    ui.errTextBrowser->setText(err);
//    ui.errTextBrowser->setStyleSheet(ui.errTextBrowser->styleSheet() + "\ncolor:red;");
//}

void MainWindow::showConnectedMessage_slot() {
    qDebug() << "MainWindow::showConnectedMessage_slot() slot called";
//    ui.errTextBrowser->setText("Connected");
//    ui.errTextBrowser->setStyleSheet(ui.errTextBrowser->styleSheet() + "color:green;");
}

void MainWindow::paintEvent(QPaintEvent *) {

    ui.mainMenuWidget->setFixedSize(this->size());
    ui.joiningWidget->setFixedSize(this->size());
    ui.roomCreationWidget->setFixedSize(this->size());
    ui.gameWidget->setFixedSize(this->size() - QSize(0, 30));
    ui.loginWidget->setFixedSize(this->size());
    ui.splashScreenWidget->setFixedSize(this->size());
    ui.roomsListWidget->setFixedSize(this->size());
}

void MainWindow::splashScreen_connections() {
    connect(ui.splashScreenWidget, &SplashScreenWidget::exit_signal, this, &MainWindow::exit_slot);
    connect(ui.splashScreenWidget, &SplashScreenWidget::tryConnect_signal, client, &Client::connectToHost_slot);
    connect(client, &Client::clientErr_signal, ui.splashScreenWidget, &SplashScreenWidget::showErr_slot);
    connect(client, &Client::clientErr_signal, ui.splashScreenWidget, &SplashScreenWidget::showErr_slot);
    connect(client, &Client::connected_signal, ui.splashScreenWidget, &SplashScreenWidget::hide);
    connect(client, &Client::connected_signal, ui.loginWidget, &LoginWidget::show);
}

void MainWindow::logging_connections() {
    connect(ui.loginWidget, &LoginWidget::tryLoggin_signal, this->client, &Client::tryLoggin_slot);
    connect(client, &Client::loginSuccess_signal, ui.loginWidget, &LoginWidget::hide);
    connect(client, &Client::loginSuccess_signal, ui.mainMenuWidget, &MainMenu::show);
    connect(ui.loginWidget, &LoginWidget::tryLoggin_signal, this->client, &Client::tryLoggin_slot);

}

void MainWindow::mainMenu_connections() {
    connect(ui.mainMenuWidget, &MainMenu::createRoomBtn_signal, ui.roomCreationWidget, &RoomCreationWidget::show);
    connect(ui.mainMenuWidget, &MainMenu::joinRoomBtn_signal, ui.roomsListWidget, &RoomsListWidget::show);
    connect(ui.mainMenuWidget, &MainMenu::exitBtn_signal, this, &MainWindow::exit_slot);
    connect(ui.roomCreationWidget, &RoomCreationWidget::backToMenu_signal,
            this, &MainWindow::showMainMenu_slot);

}

void MainWindow::roomCreation_connections() {
    connect(ui.roomCreationWidget, &RoomCreationWidget::createRoom_signal,
            client, [&]() {
                client->tryCreateRoom_slot(
                        ui.roomCreationWidget->getRoomName(),
                        ui.roomCreationWidget->getPswd());
            });
//    connect(client, &Client::roomCreated_signal, ui.gameWidget, &GameWidget::show);

    connect(client, &Client::roomCreated_signal, ui.gameConfirmationWidget, &GameConfirmationWidget::show);
    connect(client, &Client::roomCreated_signal, ui.roomCreationWidget, &RoomCreationWidget::hide);
    connect(client, &Client::roomCreated_signal, ui.roomCreationWidget, &RoomCreationWidget::clearFields);
    connect(client, &Client::roomCreated_signal, ui.loginWidget, &LoginWidget::hide);
}

void MainWindow::roomsList_connections() {
    connect(ui.roomsListWidget, &RoomsListWidget::refresh_signal, client, &Client::getRoomsList_slot);

    connect(client, &Client::roomsList_signal,
            ui.roomsListWidget, &RoomsListWidget::parseJson_slot);
    connect(ui.roomsListWidget, &RoomsListWidget::roomListItemSelected_signal,
            ui.joiningWidget, &JoiningWidget::showSelf_slot);

    connect(ui.roomsListWidget, &RoomsListWidget::backToMenu_signal, ui.mainMenuWidget, &MainMenu::show);

}

void MainWindow::gameConfirmation_connections() {


    connect(client, &Client::roomCreated_signal, ui.gameConfirmationWidget,
            &GameConfirmationWidget::userIsRoomOwner_slot);
    connect(ui.gameConfirmationWidget, &GameConfirmationWidget::backToMenu_signal, ui.mainMenuWidget, &MainMenu::show);

    connect(ui.gameConfirmationWidget, &GameConfirmationWidget::userReady_signal, client, &Client::sendUserReady_slot);
    connect(ui.gameConfirmationWidget, &GameConfirmationWidget::userNotReady_signal, client,
            &Client::sendUserNotReady_slot);


    connect(client, &Client::opponentReady_signal, ui.gameConfirmationWidget,
            &GameConfirmationWidget::opponentReady_slot);
    connect(client, &Client::opponentReady_signal, ui.gameConfirmationWidget,
            &GameConfirmationWidget::opponentNotReady_slot);

}

void MainWindow::roomJoining_connections() {
    connect(ui.joiningWidget, &JoiningWidget::backToMenu_signal,
            this, &MainWindow::showMainMenu_slot);
    connect(ui.joiningWidget, &JoiningWidget::tryJoining_signal,
            client, &Client::sendJoiningRequest_slot);
//    connect(client, &Client::joinedToRoom_signal, ui.gameWidget, &GameWidget::show);
    connect(client, &Client::joinedToRoom_signal, ui.joiningWidget, &JoiningWidget::hide);

    connect(client, &Client::joinedToRoom_signal, ui.gameConfirmationWidget, &GameConfirmationWidget::show);

}

void MainWindow::gameWidget_connections() {
    connect(ui.gameWidget, &GameWidget::move_signal, client, &Client::sendMove_slot);

    connect(ui.gameConfirmationWidget, &GameConfirmationWidget::enableStartGame_signal, ui.gameWidget,
            &GameWidget::show);
    connect(ui.gameConfirmationWidget, &GameConfirmationWidget::enableStartGame_signal, ui.gameWidget,
            &GameWidget::startGame_slot);

    connect(ui.gameWidget, &GameWidget::backToMenu_signal,
            this, &MainWindow::showMainMenu_slot);

    connect(ui.gameConfirmationWidget, &GameConfirmationWidget::roomSettingsChanged_signal, ui.gameWidget,
            &GameWidget::setSettings_slot);

    connect(client, &Client::opponentMadeMove_signal, ui.gameWidget, &GameWidget::opponentMadeMove_slot);
    connect(client, &Client::opponentMadeMove_signal, ui.gameWidget, &GameWidget::allowMoves_slot);

    connect (ui.gameWidget, &GameWidget::startAskingForMove_signal, client, &Client::startAskingForMove_slot);
}

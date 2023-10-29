#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setGUI();

    client = new Client(this);

    // ------------------------------- SplashScreen
    connect(ui.splashScreenWidget, &SplashScreenWidget::exit_signal, this, &MainWindow::exit_slot);
    connect(ui.splashScreenWidget, &SplashScreenWidget::tryConnect_signal, client, &Client::connectToHost_slot);
    connect(client, &Client::clientErr_signal, ui.splashScreenWidget, &SplashScreenWidget::showErr_slot);
    connect(client, &Client::clientErr_signal, ui.splashScreenWidget, &SplashScreenWidget::showErr_slot);
    connect(client, &Client::connected_signal, ui.splashScreenWidget, &SplashScreenWidget::hide);
    connect(client, &Client::connected_signal, ui.loginWidget, &LoginWidget::show);

    //------------------------------- loggining
    connect(ui.loginWidget, &LoginWidget::tryLoggin_signal, this->client, &Client::tryLoggin_slot);
    connect(client, &Client::loginSuccess_signal, ui.loginWidget, &LoginWidget::hide);
    connect(client, &Client::loginSuccess_signal, ui.mainMenuWidget, &MainMenu::show);
    connect(ui.loginWidget, &LoginWidget::tryLoggin_signal, this->client, &Client::tryLoggin_slot);



    // ------------------------------ Main Menu Navigation by Btn
    connect(ui.mainMenuWidget, &MainMenu::createRoomBtn_signal, ui.roomCreationWidget, &RoomCreationWidget::show);
    connect(ui.mainMenuWidget, &MainMenu::joinRoomBtn_signal, ui.roomsListWidget, &RoomsListWidget::show);
    connect(ui.mainMenuWidget, &MainMenu::exitBtn_signal, this, &MainWindow::exit_slot);
    connect(ui.roomCreationWidget, &RoomCreationWidget::backToMenu_signal,
            this, &MainWindow::showMainMenu_slot);

    //------------------------------- Room creation client-server connects
    connect(ui.roomCreationWidget, &RoomCreationWidget::createRoom_signal,
            client, [&]() {
                client->tryCreateRoom_slot(
                        ui.roomCreationWidget->getRoomName(),
                        ui.roomCreationWidget->getPswd());
            });
    connect(client, &Client::roomCreated_signal, ui.gameWidget, &GameWidget::show);

    connect(client, &Client::roomCreated_signal, ui.gameWidget, &GameWidget::startGame_slot);
    connect(client, &Client::roomCreated_signal, ui.roomCreationWidget, &RoomCreationWidget::hide);
    connect(client, &Client::roomCreated_signal, ui.roomCreationWidget, &RoomCreationWidget::clearFields);
    connect(client, &Client::roomCreated_signal, ui.loginWidget, &LoginWidget::hide);


//    connect(ui.roomCreationWidget, &RoomCreationWidget::checkRoomNameUniq_signal,
//            client, &Client::checkRoomNameUniq_slot);
//    connect(client, &Client::roomNameUniqConfirmed_signal, ui.roomCreationWidget,
//            &RoomCreationWidget::roomNameUniqConfirmed_slot);
//    connect(client, &Client::roomNameUniqNotConfirmed_signal, ui.roomCreationWidget,
//            &RoomCreationWidget::roomNameUniqNotConfirmed_slot);



    //------------------------------- Rooms list client-server connects
    connect(ui.roomsListWidget, &RoomsListWidget::refresh_signal, client, &Client::getRoomsList_slot);

    connect(client, &Client::roomsList_signal,
            ui.roomsListWidget, &RoomsListWidget::parseJson_slot);
    connect(ui.roomsListWidget, &RoomsListWidget::roomListItemSelected_signal,
            ui.joiningWidget, &JoiningWidget::showSelf_slot);





    //--------------------------------- Room Joining client-server connects
    connect(ui.joiningWidget, &JoiningWidget::backToMenu_signal,
            this, &MainWindow::showMainMenu_slot);
    connect(ui.joiningWidget, &JoiningWidget::tryJoining_signal,
            client, &Client::sendJoiningRequest_slot);
    connect(client, &Client::joinedToRoom_signal, ui.gameWidget, &GameWidget::show);
    connect(client, &Client::joinedToRoom_signal, ui.joiningWidget, &JoiningWidget::hide);
//
//    connect(client, &Client::joinedToRoom_signal, ui.gameWidget, &GameWidget::startGame_slot);
//
//    connect(client, &Client::opponentNickReceived_signal, ui.gameWidget, &GameWidget::setOpponentNick_slot);
//    connect(client, &Client::joinedToRoom_signal, ui.gameWidget,
//            [&]() { ui.gameWidget->setHostNick_slot(ui.joiningWidget->getNick()); });
//    connect(client, &Client::joinedToRoom_signal, this, [&]() { ui.joiningWidget->clearFields(); });
//    connect(client, &Client::joinedToRoom_signal, this, [&]() { ui.errTextBrowser->clear(); });

    //---------------------------------
//    connect(client, &Client::clientErr_signal, this, &MainWindow::disableGame_slot);
//    connect(client, &Client::clientErr_signal, this, [&]() { has_connection = false; });


//    connect(client, &Client::connected_signal, this, [&]() { has_connection = true; });
//    connect(client, &Client::connected_signal, this, &MainWindow::showConnectedMessage_slot);



    connect(ui.gameWidget, &GameWidget::backToMenu_signal,
            this, &MainWindow::showMainMenu_slot);

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
    ui.gameWidget->setFixedSize(this->size());

    ui.roomsListWidget->hide();
    ui.roomsListWidget->move(0, 0);
    ui.roomsListWidget->setFixedSize(this->size());

    ui.loginWidget->move((this->size() / 4).width(), (this->size() / 4).height());
    ui.loginWidget->setFixedSize(this->size() / 2);
    ui.loginWidget->hide();

    ui.splashScreenWidget->move(0, 0);
    ui.splashScreenWidget->setFixedSize(this->size() - QSize(0, 100));
    ui.splashScreenWidget->show();

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
    ui.errTextBrowser->setText("Connected");
    ui.errTextBrowser->setStyleSheet(ui.errTextBrowser->styleSheet() + "color:green;");
}

void MainWindow::paintEvent(QPaintEvent) {

    ui.mainMenuWidget->setFixedSize(this->size());
    ui.joiningWidget->setFixedSize(this->size());
    ui.roomCreationWidget->setFixedSize(this->size());
    ui.gameWidget->setFixedSize(this->size());
    ui.loginWidget->setFixedSize(this->size());
    ui.splashScreenWidget->setFixedSize(this->size());
}

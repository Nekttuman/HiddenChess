#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HiddenChess.h"
#include "Client.h"


class HiddenChess : public QMainWindow {
Q_OBJECT

public:
    HiddenChess(QWidget *parent = nullptr);

    ~HiddenChess();

private:
    Ui::HiddenChessClass ui;

    Client *client;

    bool has_connection = false;

    void paintEvent(QPaintEvent);

public slots:

    void showCreateRoomWidget_slot() { ui.roomCreationWidget->show(); }

    void showJoiningWidget_slot() { ui.joiningWidget->show(); }

    void exit_slot() { this->close(); }

    void showMainMenu_slot() { ui.mainMenuWidget->show(); }

    void showGameWidget_slot() { ui.gameWidget->show(); }

    void disableGame_slot(QString err);

    void showConnectedMessage_slot();
};

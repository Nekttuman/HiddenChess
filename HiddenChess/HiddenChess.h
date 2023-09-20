#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HiddenChess.h"
#include "Client.h"


class HiddenChess : public QMainWindow
{
    Q_OBJECT

public:
    HiddenChess(QWidget *parent = nullptr);
    ~HiddenChess();

private:
    Ui::HiddenChessClass ui;

    Client* client;

    bool has_connection = false;

    void paintEvent(QPaintEvent) {

        ui.mainMenuWidget->setFixedSize(this->size());
        ui.joiningWidget->setFixedSize(this->size());
        ui.roomCreationWidget->setFixedSize(this->size());
        ui.gameWidget->setFixedSize(this->size());
    }

public slots:
  void showCreateRoomWidget_slot() {
      ui.roomCreationWidget->show();
  }

  void showJoiningWidget_slot() {
      ui.joiningWidget->show();
  }

  void exit_slot() {
      this->close();
  }

  void showMainMenu_slot() {
      ui.mainMenuWidget->show();
  }

  void showGameWidget_slot() {
      ui.gameWidget->show();
  }

  

  void disableGame_slot(QString err) {
      ui.roomCreationWidget->disableCreateRoomBtn();
      ui.joiningWidget->disableConnectBtn();
      qDebug() << "disableGame slot called";
      ui.errTextBrowser->setText(err);
      ui.errTextBrowser->setStyleSheet(ui.errTextBrowser->styleSheet() + "\ncolor:red;");
  }

  void showConnectedMessage_slot() {
    ui.errTextBrowser->setText("Connected");
    ui.errTextBrowser->setStyleSheet(ui.errTextBrowser->styleSheet() + "color:green;");
  }


};

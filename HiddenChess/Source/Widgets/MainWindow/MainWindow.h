#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Client.h"


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindowClass ui;

    Client *client;

    bool has_connection = false;

    void paintEvent(QPaintEvent);

    void setGUI();

public slots:

    void exit_slot() { this->close(); }

    void showMainMenu_slot() { ui.mainMenuWidget->show(); }

//    void disableGame_slot(QString err);

    void showConnectedMessage_slot();
};

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Client.h"


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindowClass ui;

    Client *client;

    bool has_connection = false;

    void paintEvent(QPaintEvent *) override;
//    void resizeEvent(QResizeEvent*) override;

    void setGUI();


// set global signal-slot connections
    inline void splashScreen_connections();
    inline void logging_connections();
    inline void mainMenu_connections();
    inline void roomCreation_connections();
    inline void roomsList_connections();
    inline void roomJoining_connections();
    inline void gameConfirmation_connections();
    inline void gameWidget_connections();

public slots:

    void exit_slot() { this->close(); }

    void showMainMenu_slot() { ui.mainMenuWidget->show(); }

//    void disableGame_slot(QString err);

    void showConnectedMessage_slot();
};

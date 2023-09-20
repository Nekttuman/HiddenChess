#pragma once

#include <QWidget>
#include "ui_JoiningWidget.h"

class JoiningWidget : public QWidget {
Q_OBJECT

public:
    JoiningWidget(QWidget *parent = nullptr);

    ~JoiningWidget();

    void disableConnectBtn() { ui.connectButton->setDisabled(true); }

    void enableconnectBtn() { ui.connectButton->setDisabled(false); }

private:
    Ui::JoiningWidgetClass ui;


signals:

    void backToMenu_signal();

    void startGame_signal();

private slots:

    void emitBackToMenu_slot() { emit backToMenu_signal(); }

    void emitStartGame_slot() { emit startGame_signal(); }
};

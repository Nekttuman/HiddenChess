#pragma once

#include <QWidget>
#include "ui_JoiningWidget.h"

class JoiningWidget : public QWidget {
Q_OBJECT

public:
    JoiningWidget(QWidget *parent = nullptr);

    ~JoiningWidget();

    void disableConnectBtn() { ui.connectButton->setDisabled(true); }

    void enableConnectBtn() { ui.connectButton->setDisabled(false); }

    void clearFields();

    QString getNick(){
        return ui.nicknameLineEdit->text();
    }

private:
    Ui::JoiningWidgetClass ui;


signals:

    void backToMenu_signal();

    void tryJoining_signal(QString roomName, QString roomPasswd, QString nick);


private slots:
    void tryJoining_slot();

    void emitBackToMenu_slot() { emit backToMenu_signal(); }

};

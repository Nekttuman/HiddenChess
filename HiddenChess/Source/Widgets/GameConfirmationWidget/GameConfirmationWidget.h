#pragma once

#include <QWidget>
#include "ui_GameConfirmationWidget.h"

class GameConfirmationWidget : public QWidget {
Q_OBJECT

public:
    explicit GameConfirmationWidget(QWidget *parent = nullptr);

    ~GameConfirmationWidget() override;

private:
    Ui::GameConfirmationWidget ui;
    QString color;
    qint32 allowedFakesCount;

    bool isRoomOwner = false;
    bool isOpponentReady = false;

    void disableRoomSettings();

    void enableRoomSettings();

private slots:

    void saveSettings_slot();

public slots:
    void userIsRoomOwner_slot();
    void opponentReady_slot();
    void opponentNotReady_slot();

signals:

    void enableStartGame_signal();

    void userReady_signal();
    void userNotReady_signal();
    void backToMenu_signal();

    void roomSettingsChanged_signal(QString color, qint32 allowedFakesCount);
};

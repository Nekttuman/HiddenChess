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

    void disableSettings();

    void enableSettings();

private slots:

    void saveSettings_slot();

public slots:
    void userIsRoomOwner_slot();

signals:

    void userReady_signal();
    void backToMenu_signal();

    void roomSettingsChanged_signal(QString color, qint32 allowedFakesCount);
};

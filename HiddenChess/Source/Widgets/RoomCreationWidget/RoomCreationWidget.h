#pragma once

#include <QtWidgets>
#include "ui_RoomCreationWidget.h"

class RoomCreationWidget : public QWidget {
Q_OBJECT

public:
    RoomCreationWidget(QWidget *parent = nullptr);

    ~RoomCreationWidget();
//
//    void disableCreateRoomBtn() { ui.createRoomButton->setDisabled(true); }

    void enableCreateRoomBtn() { ui.createRoomButton->setDisabled(false); }

    QString getRoomName() { return ui.roomNameLineEdit->text(); }

    QString getPswd() { return ui.pswdLineEdit->text(); }


    void clearFields() {
        ui.pswdLineEdit->clear();
        ui.roomNameLineEdit->clear();
    }

private:
    Ui::RoomCreationWidgetClass ui;

    bool roomNameUniq = false;


signals:

    void backToMenu_signal();

    void createRoom_signal();

    void checkRoomNameUniq_signal(QString);

    // internal logic
    void fieldsCorrect_signal();

private slots:

    void emitBackToMenu_slot() { emit backToMenu_signal(); }

    void createRoomBtnPressed_slot() { emit createRoom_signal(); }

//    void validateFields_slot();

    void allowRoomCreation_slot();


public slots:

    void roomNameUniqConfirmed_slot();

//    void roomNameUniqNotConfirmed_slot();


};

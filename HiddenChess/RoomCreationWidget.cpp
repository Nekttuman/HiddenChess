#include "RoomCreationWidget.h"

RoomCreationWidget::RoomCreationWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);

    connect(this, &RoomCreationWidget::fieldsCorrect_signal,
            this, &RoomCreationWidget::allowRoomCreation_slot);
}

RoomCreationWidget::~RoomCreationWidget() {}

void RoomCreationWidget::validateFields_slot() {
    bool isValid = true;

    if (ui.pswdLineEdit->text() == ""
        || ui.pswdLineEdit->text().contains(" ")) {
        ui.roomPswdErrorLabel->show();
        isValid = false;
        disableCreateRoomBtn();
    } else {
        ui.roomPswdErrorLabel->hide();
    }

    if (ui.roomNameLineEdit->text() == ""
        || ui.roomNameLineEdit->text().contains(" ")) {
        ui.roomNameErrorLabel->show();
        ui.roomNameErrorLabel->setText("name err");
        isValid = false;
        disableCreateRoomBtn();
    } else {
        ui.roomNameErrorLabel->hide();
        emit checkRoomNameUniq_signal(ui.roomNameLineEdit->text());
    }

    if (isValid)
            emit fieldsCorrect_signal();
}

void RoomCreationWidget::allowRoomCreation_slot() {
    if (roomNameUniq) {
        ui.createRoomButton->setEnabled(true);
    }
}

void RoomCreationWidget::roomNameUniqConfirmed_slot() {
    qDebug() << "sh";
    roomNameUniq = true;

    ui.roomNameErrorLabel->hide();

}

void RoomCreationWidget::roomNameUniqNotConfirmed_slot() {
    roomNameUniq = false;

    ui.roomNameErrorLabel->setText("name already exists");
    ui.roomNameErrorLabel->show();
    disableCreateRoomBtn();
}
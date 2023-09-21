#include "JoiningWidget.h"
#include <QDebug>

JoiningWidget::JoiningWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
    ui.roomPswdErrorLabel->hide();
}

JoiningWidget::~JoiningWidget() {}


void JoiningWidget::tryJoining_slot(){
        qDebug()<<"JoiningWidget tryJoining slot called";
        ui.roomNameErrorLabel->hide();
        emit tryJoining_signal(ui.roomNameLineEdit->text(), ui.pswdLineEdit->text());
}
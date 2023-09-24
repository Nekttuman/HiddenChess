#include "JoiningWidget.h"
#include <QDebug>

JoiningWidget::JoiningWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
}

JoiningWidget::~JoiningWidget() {}


void JoiningWidget::tryJoining_slot(){
        qDebug()<<"JoiningWidget tryJoining slot called";
        emit tryJoining_signal(ui.roomNameLineEdit->text(), ui.pswdLineEdit->text(), ui.nicknameLineEdit->text());
}

void JoiningWidget::clearFields(){
    ui.pswdLineEdit->clear();
    ui.nicknameLineEdit->clear();
    ui.roomNameLineEdit->clear();
}
//
// Created by 79140 on 10/14/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWidget.h" resolved

#include "loginwidget.h"
#include "ui_loginwidget.h"


LoginWidget::LoginWidget(QWidget *parent) :
        QWidget(parent) {
    ui.setupUi(this);
    ui.pswdLineEdit->setEchoMode(QLineEdit::Password);

    connect(ui.loginBtn, &QPushButton::clicked, this, &LoginWidget::emitTryLogin_slot);
}

void LoginWidget::emitTryLogin_slot() {
    qDebug()<<"LoginWidget::emitTryLogin_slot slot called";
    emit tryLoggin_signal(
            ui.loginLineEdit->text(),
            ui.pswdLineEdit->text()
    );
    ui.errLabel->setText("");
}

LoginWidget::~LoginWidget() {
}

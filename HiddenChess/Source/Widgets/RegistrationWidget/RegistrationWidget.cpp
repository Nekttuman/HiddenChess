//
// Created by 79140 on 12/4/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RegistrationWidget.h" resolved

#include "RegistrationWidget.h"
#include "ui_RegistrationWidget.h"


RegistrationWidget::RegistrationWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::RegistrationWidget) {
    ui->setupUi(this);

//    connect(ui.)
}

RegistrationWidget::~RegistrationWidget() {
    delete ui;
}

void RegistrationWidget::validateFields() {
    QString login = ui->loginLineEdit->text();
    QString pswd = ui->pswdLineEdit->text();
    QString pswdRep = ui->repeatPswdLineEdit->text();


    if (pswd != pswdRep)
        ui->errLabel->setText("Passwords are not the same");
    else if (login.trimmed().isEmpty())
        ui->errLabel->setText("Login cannot be empty");
    else if (pswd.length() < 8)
        ui->errLabel->setText("Too short password");
    else
            emit registerSignal(login, pswd);
}

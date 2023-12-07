//
// Created by 79140 on 10/14/2023.
//

#ifndef HIDDENCHESS_LOGINWIDGET_H
#define HIDDENCHESS_LOGINWIDGET_H

#include <QWidget>
#include <QDebug>
#include "ui_loginwidget.h"

class LoginWidget : public QWidget {
Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);

    ~LoginWidget() override;

private:
    Ui::LoginWidget ui;

private slots:

    void emitTryLogin_slot();

public slots:

    void showErr_slot(QString err) {
        ui.errLabel->setText(err);
    }

signals:

    void tryLoggin_signal(QString login, QString pswd);

    void goToRegistration_signal();
};


#endif //HIDDENCHESS_LOGINWIDGET_H

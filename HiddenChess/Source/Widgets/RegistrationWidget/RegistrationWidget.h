//
// Created by 79140 on 12/4/2023.
//

#ifndef HIDDENCHESS_REGISTRATIONWIDGET_H
#define HIDDENCHESS_REGISTRATIONWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class RegistrationWidget; }
QT_END_NAMESPACE

class RegistrationWidget : public QWidget {
Q_OBJECT

public:
    explicit RegistrationWidget(QWidget *parent = nullptr);

    ~RegistrationWidget() override;

private:
    Ui::RegistrationWidget *ui;


signals:

    void register_signal(const QString &login, const QString &pswd);

    void backToLogin_signal();

private slots:

    void validateFields();
public slots:
    void showErr_slot(QString err);

};


#endif //HIDDENCHESS_REGISTRATIONWIDGET_H

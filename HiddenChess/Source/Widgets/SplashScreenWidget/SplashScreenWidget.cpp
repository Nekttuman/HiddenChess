//
// Created by 79140 on 10/19/2023.
//

#include "SplashScreenWidget.h"


SplashScreenWidget::SplashScreenWidget(QWidget *parent) :
        QWidget(parent) {
    ui.setupUi(this);
    qDebug() << pixmaps.first.load(":/MainWindow/AnotherPics/pop1.png");
    qDebug() << pixmaps.second.load(":/MainWindow/AnotherPics/pop2.png");


    pixmaps.first = pixmaps.first.scaled(QSize(300, 300));
    pixmaps.second = pixmaps.second.scaled(QSize(300, 300));


    connect(ui.reconnectButton, &QPushButton::pressed, this, [&]() { reconnectBtnAction(); });
    connect(ui.reconnectButton, &QPushButton::released, this, &SplashScreenWidget::backNormal);

    connect(ui.exitButton, &QPushButton::released, this, [&]() { emit exit_signal(); });
    backNormal();
    emit tryConnect_signal();
}

SplashScreenWidget::~SplashScreenWidget() {

}

void SplashScreenWidget::reconnectBtnAction() {
    emit tryConnect_signal();
    ui.label->setText("Connecting...");
    makePop();
}

void SplashScreenWidget::makePop() {
    ui.labelForMovie->setPixmap(pixmaps.second);
    QSound::play(":/MainWindow/Sounds/cat1.wav");
}

void SplashScreenWidget::backNormal() {
    ui.labelForMovie->setPixmap(pixmaps.first);
}


void SplashScreenWidget::showErr_slot(QString err) {
    ui.label->setText(err);
}


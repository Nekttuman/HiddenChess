//
// Created by 79140 on 10/19/2023.
//
#pragma once

#include <QWidget>
#include <QPixmap>
#include <QSound>
#include <QDebug>
#include "ui_SplashScreenWidget.h"



class SplashScreenWidget : public QWidget {
Q_OBJECT

public:
    explicit SplashScreenWidget(QWidget *parent = nullptr);

    ~SplashScreenWidget() override;

public slots:
    void showErr_slot(QString err);

private:
    Ui::SplashScreenWidget ui;

    QPair<QPixmap, QPixmap> pixmaps;

    void makePop();
    void backNormal();
    void reconnectBtnAction();
signals:
    void exit_signal();
    void tryConnect_signal();


};


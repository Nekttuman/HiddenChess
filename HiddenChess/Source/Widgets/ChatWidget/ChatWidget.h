#pragma once

#include <QtWidgets>
#include <QtWebSockets/QtWebSockets>
#include "ui_ChatWidget.h"

class ChatWidget : public QWidget {
Q_OBJECT

public:
    ChatWidget(QWidget *parent = nullptr);

    ~ChatWidget();
public slots:
    void onConnected() {
        qDebug() << "Connected to the server";
    }

    void onDisconnected() {
        qDebug() << "Disconnected from the server";
    }

    void onTextMessageReceived(QString message) {
        qDebug() << "Received message: " << message;
        // Handle the received message (e.g., display it in your UI)
    }

    void sendMessage(QString message) {
        websocket->sendTextMessage(message);
    }


private:
    QWebSocket *websocket;

    Ui::ChatWidgetClass ui;
};

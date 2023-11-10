#include "ChatWidget.h"

ChatWidget::ChatWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
    websocket = new QWebSocket();
    QObject::connect(websocket, &QWebSocket::connected, this, &ChatWidget::onConnected);
    QObject::connect(websocket, &QWebSocket::disconnected, this, &ChatWidget::onDisconnected);
    QObject::connect(websocket, &QWebSocket::textMessageReceived, this, &ChatWidget::onTextMessageReceived);

    // Replace with the URL of your WebSocket server (e.g., "ws://localhost:8000/ws/chat/room_name/")
    QUrl url("ws://localhost:8000/ws/chat/room_name/");

//    websocket->open(url);
}

ChatWidget::~ChatWidget() {}

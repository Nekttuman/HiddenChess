#include "Client.h"


Client::Client(QObject *parent)
        : QObject(parent) {
    socket = new QTcpSocket;

    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead_slot);
    //connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    connect(socket, &QTcpSocket::connected, this, [&]() { emit connected_signal(); });
    connect(socket, &QTcpSocket::disconnected, socket, [&]() { emit clientErr_signal("disconnected"); });
    connect(socket, &QTcpSocket::errorOccurred, socket, [&]() { emit clientErr_signal("connection error"); });

}

Client::~Client() {}

void Client::SendToServer(QString str) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt)
    out << quint16(0) << clientRequestType::chatMess << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);

}

void Client::connectToHost_slot() {
    if (socket->state() == QAbstractSocket::SocketState::ConnectedState)
        return;
    try {
        socket->connectToHost("127.0.0.1", 2323);
    }
    catch (...) {
        emit clientErr_signal("programm error");
        return;
    }
    if (socket->state() == QAbstractSocket::SocketState::ConnectingState) {
        emit clientErr_signal("connecting...");
    }
}

void Client::tryCreateRoom(QString roomName, QString pswd) {
    if (socket->state() != QAbstractSocket::SocketState::ConnectedState) {
        emit clientErr_signal("not connected");
        return;
    }

    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out << quint16(0) << clientRequestType::createRoom << roomName << pswd;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);


}




void Client::readyRead_slot() {
    QDataStream in(socket);

    if (in.status() == QDataStream::Ok) {


        while (true) {
            if (nextBlockSize == 0) {
                if (socket->bytesAvailable() < 2)
                    break;
                in >> nextBlockSize;
            }
            if (socket->bytesAvailable() < nextBlockSize)
                break;


            serverResponceType rt;
            in >> rt;
            qDebug() << rt;
            if (rt == serverResponceType::roomCreationErr) {
                QString err;
                in >> err;
                emit clientErr_signal(err);
            } else if (rt == serverResponceType::roomCreated) {
                emit roomCreated_signal();
            } else if (rt == serverResponceType::roomNameCheckFailed) {
                emit roomNameUniqNotConfirmed_signal();
            } else if (rt == serverResponceType::roomNameCheckPassed) {
                emit roomNameUniqConfirmed_signal();
            }


            nextBlockSize = 0;

            break;
        }

    } else
        qDebug() << "read err";
}


void Client::checkRoomNameUniq_slot(QString roomName) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out << quint16(0) << clientRequestType::checkRoomNameUniq << roomName;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
}
#pragma once

#include <QObject>
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>

#include "Room.h"

enum serverResponcesType {
    roomNameCheckFailed,
    roomNameCheckPassed,
    roomCreated,
    roomCreationErr
};
enum clientRequestType {
    tryConnectToRoom,
    createRoom,
    chatMess,
    move,
    surrenderCommand,
    checkRoomNameUniq
};


class Server : public QTcpServer {
Q_OBJECT

public:
    Server();

    ~Server();

    QTcpSocket *socket;

private:
    QVector<QTcpSocket *> m_sockets;
    quint16 m_nextBlockSize = 0;

    QVector<Room *> m_rooms;

    void SendToClient(QString str);


    void createRoom(QString roomName, QString pswd, QTcpSocket *sender);

    void checkRoomNameUniq(QString name, QTcpSocket *sender);
    bool isUniq(QString roomName) ;

public slots:

    void incomingConnection(qintptr socketDescriptor) override;

    void slotReadyRead();

private slots:

    void disconnectSocket();
};

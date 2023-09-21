#pragma once

#include <QObject>
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>

#include "Room.h"

enum serverResponseType {
    roomNameCheckFailed,
    roomNameCheckPassed,
    roomCreated,
    roomCreationErr,

    JoiningErrNoRoom,
    JoiningErrWrongPswd,
    JoiningErrRoomFull,
    JoinedToRoom
};

enum clientRequestType {
    createRoom,
    chatMess,
    move,
    surrenderCommand,
    checkRoomNameUniq,
    tryJoiningToRoom
};

class Server : public QTcpServer {
Q_OBJECT

    int prevId = 0;
public:
    Server();

    ~Server();

    QTcpSocket *socket;

private:
    QVector<QTcpSocket *> m_sockets;
    quint16 m_nextBlockSize = 0;


    using roomId = int;

    QMap<roomId, Room*> M_rooms;

    void SendToClient(QString str);


    void createRoom(QString roomName, QString pswd, QTcpSocket *sender);

    void checkRoomNameUniq(QString name, QTcpSocket *sender);
    bool isUniq(const QString& roomName) ;
    void tryJoinToRoom(const QString& roomName, QString roomPasswd, QTcpSocket *sender);
    roomId getRoomId(const QString& roomName);

public slots:

    void incomingConnection(qintptr socketDescriptor) override;

    void slotReadyRead();

private slots:

    void disconnectSocket();
};

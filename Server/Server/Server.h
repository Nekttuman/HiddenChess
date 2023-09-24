#pragma once

#include <QObject>
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>

#include "Room.h"

enum clientRequestType {
    createRoom,
    chatMess,
    move,
    surrenderCommand,
    checkRoomNameUniq,
    tryJoiningToRoom,
    getOpponentNick
};

enum serverResponseType {
    roomNameCheckFailed,
    roomNameCheckPassed,
    roomCreated,
    roomCreationErr,

    JoiningErrNoRoom,
    JoiningErrWrongPswd,
    JoiningErrRoomFull,
    JoinedToRoom,
    OpponentNick,

};
class Server : public QTcpServer {
Q_OBJECT
// TODO: create roomManager, in server create func
//  sendResponce(serverResponseType rt, QList<QString> responseParams)
//  and send everything throw it
//  getRequest(clientRequestType rt, QList<QString> requestParams) analogically
//  and have one instance of roomManager in server


    int prevId = 0;
public:
    Server();

    ~Server();

    QTcpSocket *socket;

private:
    QVector<QTcpSocket *> m_sockets;
    quint16 m_nextBlockSize = 0;
    QByteArray m_data;


    using roomId = int;

    QMap<roomId, Room*> M_rooms;

    void createRoom(QString roomName, QString pswd, QString hostNick, QTcpSocket *sender);
    void sendNick(const QString& nick, QTcpSocket * receiver);

    void checkRoomNameUniq(QString name, QTcpSocket *sender);
    bool isUniq(const QString& roomName) ;
    void tryJoinToRoom(const QString &roomName, QString roomPasswd, QString nick, QTcpSocket *receiver);
    roomId getRoomId(const QString& roomName);

public slots:

    void incomingConnection(qintptr socketDescriptor) override;

    void slotReadyRead();

private slots:

    void disconnectSocket();
};

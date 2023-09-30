#pragma once

#include <QObject>
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>

#include "RoomsManager.h"


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

public:
    Server();

    ~Server();

    QTcpSocket *socket;


    using RoomId = int;

private:
    QMap <qintptr,QTcpSocket*> m_sockets;
    quint16 m_nextBlockSize = 0;
    QByteArray m_data;

    RoomsManager *roomsManager;


public slots:

    void incomingConnection(qintptr socketDescriptor) override;

    void slotReadyRead();
    void sendResponse_slot(qintptr socketDescriptor, serverResponseType rt, const QList<QString>& responseParams);


private slots:

    void disconnectSocket();
};

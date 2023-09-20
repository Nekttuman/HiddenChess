#pragma once

#include <QObject>
#include <QTcpSocket>
#include <qdatastream.h>


enum clientRequestType {
    tryConnectToRoom,
    createRoom,
    chatMess,
    move,
    surrenderCommand,
    checkRoomNameUniq
};

enum serverResponceType {
    roomNameCheckFailed,
    roomNameCheckPassed,
    roomCreated,
    roomCreationErr
};


class Client : public QObject {
Q_OBJECT

public:
    Client(QObject *parent);

    ~Client();

    void tryCreateRoom(QString roomName, QString pswd);

signals:

    void clientErr_signal(QString);

    void connected_signal();

    void roomNameUniqConfirmed_signal();

    void roomNameUniqNotConfirmed_signal();

    void roomCreated_signal();

public slots:

    void readyRead_slot();

    void connectToHost_slot();

    void checkRoomNameUniq_slot(QString roomName);

private:
    QTcpSocket *socket;
    QByteArray Data;
    quint16 nextBlockSize = 0;

    void SendToServer(QString str);
};

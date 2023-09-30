#pragma once

#include <QObject>
#include <QTcpSocket>
#include <qdatastream.h>

enum clientRequestType {
    createRoom,
    chatMess,
    move,
    surrenderCommand,
    checkRoomNameUniq,
    tryJoiningToRoom
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
    OpponentNick
};

class Client : public QObject {
Q_OBJECT

    using RoomId = int;
public:
    Client(QObject *parent);

    ~Client();

    void tryCreateRoom(QString roomName, QString pswd, QString hostNick);

signals:

    void clientErr_signal(QString);

    void connected_signal();

    void roomNameUniqConfirmed_signal();

    void roomNameUniqNotConfirmed_signal();

    void roomCreated_signal();

    void joinedToRoom();

    void opponentNickReceived_signal(QString opponentNick);

public slots:

    void readyRead_slot();

    void connectToHost_slot();

    void checkRoomNameUniq_slot(QString roomName); //for creating
    void sendJoiningRequest_slot(QString roomName, QString roomPasswd, QString nick); // for joining

private:
    QTcpSocket *m_socket;
    QByteArray m_data;
    quint16 m_nextBlockSize = 0;
    RoomId m_currentRoom = -1;

    void SendToServer(QString str);
};

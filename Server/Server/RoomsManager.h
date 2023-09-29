//
// Created by 79140 on 9/29/2023.
//

#ifndef SERVER_ROOMSMANAGER_H
#define SERVER_ROOMSMANAGER_H

#include <QObject>


#include "Room.h"

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

class RoomsManager: QObject {
    Q_OBJECT

    using RoomId = int;

    QMap<RoomId, Room *> M_rooms;


    int prevId = 0;


public:
    RoomsManager() {  }

    void createRoom(const QString& roomName, const QString& pswd, QString hostNick, qintptr roomHostSocketDescriptor);

    void checkRoomNameUniq(const QString& name, qintptr socketDescriptor);

    void tryJoinToRoom(const QString &roomName, QString roomPasswd, QString nick, qintptr socketDescriptor);

    RoomId getRoomId(const QString &roomName);

    void sendOpponentNick(qintptr receiverSocketDescriptor, RoomId roomid);

signals:

    void sendResponse_signal(qintptr socketDescriptor, serverResponseType rt, QList<QString> responseParams);

private:

    bool isUniq(const QString &roomName);
};


#endif //SERVER_ROOMSMANAGER_H

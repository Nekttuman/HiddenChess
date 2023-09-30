#include "RoomsManager.h"

#include <utility>


void
RoomsManager::createRoom(const QString &roomName, const QString &pswd, QString hostNick,
                         qintptr roomHostSocketDescriptor) {

    if (!isUniq(roomName)) {
        sendResponse_signal(roomHostSocketDescriptor, serverResponseType::roomCreationErr, {"Not uniq room name"});
        return;
    }
    M_rooms[prevId] = new Room(roomHostSocketDescriptor, roomName, pswd);
    M_rooms[prevId]->setHostNick(std::move(hostNick));


    qDebug() << "room created: " << roomName << pswd << M_rooms[prevId]->getHostNick();
    ++prevId;
    sendResponse_signal(roomHostSocketDescriptor, serverResponseType::roomCreated, {});
}

void RoomsManager::checkRoomNameUniq(const QString &name, qintptr roomHostSocketDescriptor) {
    if (isUniq(name))
        sendResponse_signal(roomHostSocketDescriptor, serverResponseType::roomNameCheckPassed, {});
    else
        sendResponse_signal(roomHostSocketDescriptor, serverResponseType::roomNameCheckFailed, {});
}

bool RoomsManager::isUniq(const QString &roomName) {
    for (auto room: M_rooms) {
        if (room->getName() == roomName)
            return false;
    }
    return true;
}

void RoomsManager::tryJoinToRoom(const QString &roomName, const QString& roomPasswd, QString nick, qintptr socketDescriptor) {
    auto roomId = getRoomId(roomName);
    if (roomId == -1) {
        sendResponse_signal(socketDescriptor, serverResponseType::JoiningErrNoRoom, {});
        return;
    }
    auto room = M_rooms[roomId];
    if (!room->checkPswd(roomPasswd)) {
        sendResponse_signal(socketDescriptor, serverResponseType::JoiningErrWrongPswd, {});
        return;
    }
    if (room->hasOpponent()) {
        sendResponse_signal(socketDescriptor, serverResponseType::JoiningErrRoomFull, {});
        return;
    }

    room->addOpponent(socketDescriptor, nick);

    sendResponse_signal(socketDescriptor, serverResponseType::JoinedToRoom,
                        {QString::number(roomId), room->getHostNick()});
    qDebug() << "joined to" << roomId << room->getHostNick();

    sendResponse_signal(room->getHostSocketDescriptor(), serverResponseType::OpponentNick, {std::move(nick)});
    sendResponse_signal(socketDescriptor, serverResponseType::OpponentNick, {room->getHostNick()});
}

RoomsManager::RoomId RoomsManager::getRoomId(const QString &roomName) {
    for (auto roomId = M_rooms.keyBegin(); roomId != M_rooms.keyEnd(); ++roomId) {
        if (M_rooms[*roomId]->getName() == roomName)
            return *roomId;
    }
    return -1;
}



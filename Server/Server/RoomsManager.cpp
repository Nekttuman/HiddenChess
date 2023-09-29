//
// Created by 79140 on 9/29/2023.
//

#include "RoomsManager.h"


void
RoomsManager::createRoom(const QString &roomName, const QString &pswd, QString hostNick,
                         qintptr roomHostSocketDescriptor) {

    if (!isUniq(roomName)) {
        sendResponse_signal(roomHostSocketDescriptor, serverResponseType::roomCreationErr, {"Not uniq room name"});
        return;
    }
    M_rooms[prevId] = new Room(roomHostSocketDescriptor, roomName, pswd);
    M_rooms[prevId]->setHostNick(hostNick);
    ++prevId;

    qDebug() << "room created: " << roomName << pswd;

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

void RoomsManager::tryJoinToRoom(const QString &roomName, QString roomPasswd, QString nick, qintptr socketDescriptor) {

    // TODO: rewrite with serverResponseType::roomCreationErr and responceParams as describtion of err,
    //         or rewrite serverResponseType::roomCreationErr usage

    auto roomId = getRoomId(roomName);
    if (roomId == -1) {
        sendResponse_signal(socketDescriptor, serverResponseType::JoiningErrNoRoom, {});
        return;
    }
    auto room = M_rooms[roomId];
    if (!room->checkPswd(std::move(roomPasswd))) {
        sendResponse_signal(socketDescriptor, serverResponseType::JoiningErrWrongPswd, {});
        return;
    }
    if (room->hasOpponent()) {
        sendResponse_signal(socketDescriptor, serverResponseType::JoiningErrRoomFull, {});
        return;
    }

    room->add_oponent(socketDescriptor);

    sendResponse_signal(socketDescriptor, serverResponseType::JoiningErrRoomFull, {QString(roomId)});
    qDebug() << "joined to" << roomId;

    sendResponse_signal(room->getHostSocket(), serverResponseType::OpponentNick, { nick});
}

RoomsManager::RoomId RoomsManager::getRoomId(const QString &roomName) {
    for (auto roomId = M_rooms.keyBegin(); roomId != M_rooms.keyEnd(); ++roomId) {
        if (M_rooms[*roomId]->getName() == roomName)
            return *roomId;
    }
    return -1;
}

void RoomsManager::sendOpponentNick(qintptr receiverSocketDescriptor, RoomId roomid) {
auto room = M_rooms[roomid];
if (room==nullptr){
    sendResponse_signal(receiverSocketDescriptor, serverResponseType::JoiningErrNoRoom, {});
    return;
}
    sendResponse_signal(room->getHostSocket(), serverResponseType::OpponentNick, { room->getOpponentNick(receiverSocketDescriptor)});
}




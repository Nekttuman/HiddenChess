#include "Server.h"

#include <utility>


Server::Server() {
    if (this->listen(QHostAddress::Any, 2323))
        qDebug() << "server started";
    else
        qDebug() << "error";
}

Server::~Server() {}



void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnectSocket);

    m_sockets.push_back(socket);
    qDebug() << "client connected " << socketDescriptor;
}


void Server::slotReadyRead() {
    socket = (QTcpSocket *) sender();
    QDataStream in(socket);

    //in.setVersion(QDataStream::Qt_6_2);

    if (in.status() == QDataStream::Ok) {

        while (true) {
            if (m_nextBlockSize == 0) {
                qDebug() << "next blockSize = 0";
                if (socket->bytesAvailable() < 2) {
                    qDebug() << "Data<2, break";
                    break;
                }
                in >> m_nextBlockSize;
            }
            if (socket->bytesAvailable() < m_nextBlockSize) {
                qDebug() << "data not full, break";
                break;
            }

            clientRequestType requestType;

            in >> requestType;
            qDebug() << requestType;
            if (requestType == clientRequestType::createRoom) {
                QString roomName, pswd, hostNick;
                in >> roomName >> pswd >> hostNick;
                createRoom(roomName, pswd, hostNick, socket);
            }
            if (requestType == clientRequestType::checkRoomNameUniq) {
                QString roomName;
                in >> roomName;
                checkRoomNameUniq(roomName, socket);
            }
            if (requestType == clientRequestType::tryJoiningToRoom) {
                QString roomName, roomPasswd, nick;
                in >> roomName >> roomPasswd >> nick;

                qDebug() << "joining room request" << roomName << roomPasswd << nick;
                tryJoinToRoom(roomName, roomPasswd, nick, socket);
            }
            if (requestType == clientRequestType::getOpponentNick) {
                roomId room;
                in >> room;
                QString opponentNick = M_rooms[room]->getOpponentNick(socket);
                sendNick(opponentNick, socket);
            }


            m_nextBlockSize = 0;
            break;
        }
    } else
        qDebug() << "data stream err";
}

void Server::sendNick(const QString &nick, QTcpSocket *receiver) {
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << quint16(0) << serverResponseType::OpponentNick << nick;
    out.device()->seek(0);
    out << quint16(m_data.size() - sizeof(quint16));

    receiver->write(m_data);
}

void Server::disconnectSocket() {
    // TODO: delete related rooms

    qDebug() << "client disconnected " << socket->localAddress();
    m_sockets.erase(std::remove(m_sockets.begin(), m_sockets.end(), socket), m_sockets.end());

    socket->deleteLater();
}

void Server::createRoom(QString roomName, QString pswd, QString hostNick, QTcpSocket *sender) {
m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    if (!isUniq(roomName)) {
        out << quint16(0) << serverResponseType::roomCreationErr << "Not uniq name";
        out.device()->seek(0);
        out << quint16(m_data.size() - sizeof(quint16));
        sender->write(m_data);
        return;
    }
    M_rooms[prevId] = new Room(sender, roomName, pswd);
    M_rooms[prevId]->setHostNick(hostNick);
    ++prevId;
    qDebug() << "room created: " << roomName << pswd;

    out << quint16(0) << serverResponseType::roomCreated;
    out.device()->seek(0);
    out << quint16(m_data.size() - sizeof(quint16));
    sender->write(m_data);

    for (auto room: M_rooms) {
        qDebug() << room->getName();
    }


}

void Server::checkRoomNameUniq(QString name, QTcpSocket *sender) {

    QDataStream out(&m_data, QIODevice::WriteOnly);
    if (isUniq(name)) {

        qDebug() << name << "uniq";
        out << quint16(0) << serverResponseType::roomNameCheckPassed;
        out.device()->seek(0);
        out << quint16(m_data.size() - sizeof(quint16));
    } else {
        qDebug() << name << "not uniq";
        out << quint16(0) << serverResponseType::roomNameCheckFailed;
        out.device()->seek(0);
        out << quint16(m_data.size() - sizeof(quint16));
    }

    sender->write(m_data);
}

bool Server::isUniq(const QString &roomName) {
    for (auto room: M_rooms) {
        if (room->getName() == roomName)
            return false;
    }
    return true;
}

void Server::tryJoinToRoom(const QString &roomName, QString roomPasswd, QString nick, QTcpSocket *receiver) {
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);

    auto roomId = getRoomId(roomName);
    if (roomId == -1) {
        out << quint16(0) << serverResponseType::JoiningErrNoRoom;
        out.device()->seek(0);
        out << quint16(m_data.size() - sizeof(quint16));
        receiver->write(m_data);
        return;
    }


    auto room = M_rooms[roomId];
    if (!room->checkPswd(std::move(roomPasswd))) {
        out << quint16(0) << serverResponseType::JoiningErrWrongPswd;
        out.device()->seek(0);
        out << quint16(m_data.size() - sizeof(quint16));
        receiver->write(m_data);
        return;
    }

    if (room->hasOpponent()) {
        out << quint16(0) << serverResponseType::JoiningErrRoomFull;
        out.device()->seek(0);
        out << quint16(m_data.size() - sizeof(quint16));
        receiver->write(m_data);
        return;
    }

    room->add_oponent(receiver);
    out << quint16(0) << serverResponseType::JoinedToRoom << roomId;
    out.device()->seek(0);
    out << quint16(m_data.size() - sizeof(quint16));
    qDebug() << "joined to" << roomId;
    receiver->write(m_data);

    sendNick(nick, room->getHostSocket());

}

Server::roomId Server::getRoomId(const QString &roomName) {
    for (auto roomId = M_rooms.keyBegin(); roomId != M_rooms.keyEnd(); ++roomId) {
        if (M_rooms[*roomId]->getName() == roomName)
            return *roomId;
    }
    return -1;
}

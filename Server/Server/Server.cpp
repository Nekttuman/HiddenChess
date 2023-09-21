#include "Server.h"

#include <utility>


Server::Server() {
    if (this->listen(QHostAddress::Any, 2323))
        qDebug() << "server started";
    else
        qDebug() << "error";
}

Server::~Server() {}

void Server::SendToClient(QString str) {
    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt)
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));

    qDebug() << str;

    for (auto it = m_sockets.begin(); it != m_sockets.end(); ++it) {
        (*it)->write(Data);
    }
}

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

            clientRequestType mt;

            in >> mt;
            qDebug() << mt;
            if (mt == clientRequestType::createRoom) {
                QString roomName, pswd;
                in >> roomName >> pswd;
                createRoom(roomName, pswd, socket);
            }
            if (mt == clientRequestType::checkRoomNameUniq) {
                QString roomName;
                in >> roomName;
                checkRoomNameUniq(roomName, socket);
            }
            if (mt == clientRequestType::tryJoiningToRoom) {
                QString roomName, roomPasswd;
                in >> roomName >> roomPasswd;

                qDebug()<<"joining room request"<<roomName<<roomPasswd;
                tryJoinToRoom(roomName, roomPasswd, socket);
            }


            m_nextBlockSize = 0;
            break;
        }
    } else
        qDebug() << "data stream err";
}

void Server::disconnectSocket() {
    // TODO: delete related rooms

    qDebug() << "client disconnected " << socket->localAddress();
    m_sockets.erase(std::remove(m_sockets.begin(), m_sockets.end(), socket), m_sockets.end());

    socket->deleteLater();
}

void Server::createRoom(QString roomName, QString pswd, QTcpSocket *sender) {

    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    if (!isUniq(roomName)) {
        out << quint16(0) << serverResponseType::roomCreationErr << "Not uniq name";
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));
        sender->write(Data);
        return;
    }
    M_rooms[++prevId] = new Room(sender, roomName, pswd);
    qDebug() << "room created: " << roomName << pswd;

    out << quint16(0) << serverResponseType::roomCreated;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    sender->write(Data);

    for (auto room: M_rooms) {
        qDebug() << room->getName();
    }


}

void Server::checkRoomNameUniq(QString name, QTcpSocket *sender) {

    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    if (isUniq(name)) {

        qDebug() << name << "uniq";
        out << quint16(0) << serverResponseType::roomNameCheckPassed;
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));
    } else {
        qDebug() << name << "not uniq";
        out << quint16(0) << serverResponseType::roomNameCheckFailed;
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));
    }

    sender->write(Data);
}

bool Server::isUniq(const QString& roomName) {
    for (auto room: M_rooms) {
        if (room->getName() == roomName)
            return false;
    }
    return true;
}

void Server::tryJoinToRoom(const QString& roomName, QString roomPasswd, QTcpSocket *sender) {
    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);

    auto roomId = getRoomId(roomName);
    if (roomId == -1){
        out << quint16(0) << serverResponseType::JoiningErrNoRoom;
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));
        sender->write(Data);
        return;
    }


    auto room = M_rooms[roomId];
    if (!room->checkPswd(std::move(roomPasswd))){
        out << quint16(0) << serverResponseType::JoiningErrWrongPswd;
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));
        sender->write(Data);
        return;
    }

    if (room->hasOpponent()){
        out << quint16(0) << serverResponseType::JoiningErrRoomFull;
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));
        sender->write(Data);
        return;
    }

    room->add_oponent(sender);
    out << quint16(0) << serverResponseType::JoinedToRoom << roomId;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    qDebug()<<"joined to"<<roomId;
    sender->write(Data);

}

Server::roomId Server::getRoomId(const QString& roomName) {
    for (auto roomId = M_rooms.keyBegin(); roomId != M_rooms.keyEnd(); ++roomId){
        if (M_rooms[*roomId]->getName() == roomName)
            return *roomId;
    }
    return -1;
}

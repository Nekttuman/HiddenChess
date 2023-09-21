#include "Server.h"


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
        out << quint16(0) << serverResponcesType::roomCreationErr << "Not uniq name";
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));
        sender->write(Data);
        return;
    }
    m_rooms.push_back(new Room(sender, roomName, pswd));
    qDebug() << "room created: " << roomName << pswd;

    out << quint16(0) << serverResponcesType::roomCreated;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    sender->write(Data);

    for (auto room: m_rooms) {
        qDebug() << room->getName();
    }


}

void Server::checkRoomNameUniq(QString name, QTcpSocket *sender) {

    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    if (isUniq(name)) {

        qDebug() << name << "uniq";
        out << quint16(0) << serverResponcesType::roomNameCheckPassed;
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));
    } else {
        qDebug() << name << "not uniq";
        out << quint16(0) << serverResponcesType::roomNameCheckFailed;
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));
    }

    sender->write(Data);
}

bool Server::isUniq(QString roomName) {
    for (auto room: m_rooms) {
        if (room->getName() == roomName)
            return false;
    }
    return true;
}
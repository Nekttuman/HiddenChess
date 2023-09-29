#include "Server.h"

#include <utility>


Server::Server() {
    if (this->listen(QHostAddress::Any, 2323))
        qDebug() << "server started";
    else
        qDebug() << "error";

    roomsManager = new RoomsManager();

    Server::connect(roomsManager, &RoomsManager::sendResponse_signal, this, &Server::sendResponce_slot);
}

Server::~Server() {
    delete roomsManager;
    delete socket;
}


void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnectSocket);

    m_sockets[socket->socketDescriptor()] = socket;
    qDebug() << "client connected " << socketDescriptor;
}


void Server::slotReadyRead() {
    socket = (QTcpSocket *) sender();
    QDataStream in(socket);

    if (in.status() == QDataStream::Ok) {
        while (true) {
            if (m_nextBlockSize == 0) {
                if (socket->bytesAvailable() < 2)
                    break;
                in >> m_nextBlockSize;
            }
            if (socket->bytesAvailable() < m_nextBlockSize)
                break;


            clientRequestType requestType;

            in >> requestType;
            qDebug() << requestType;

            switch (requestType) {
                case clientRequestType::createRoom: {
                    QString roomName, pswd, hostNick;
                    in >> roomName >> pswd >> hostNick;
                    roomsManager->createRoom(roomName, pswd, hostNick, socket->socketDescriptor());
                    break;
                }
                case clientRequestType::checkRoomNameUniq: {
                    QString roomName;
                    in >> roomName;
                    roomsManager->checkRoomNameUniq(roomName, socket->socketDescriptor());
                    break;
                }
                case clientRequestType::tryJoiningToRoom: {
                    QString roomName, roomPasswd, nick;
                    in >> roomName >> roomPasswd >> nick;
                    roomsManager->tryJoinToRoom(roomName, roomPasswd, nick, socket->socketDescriptor());
                    break;
                }
                case clientRequestType::getOpponentNick: {
                    roomId room;
                    in >> room;
                    roomsManager->sendOpponentNick(socket->socketDescriptor(), roomId room);
                    break;
                }
                default:{
                    qDebug()<<"not handled request: "<<requestType;
                }
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
    m_sockets.erase(std::remove(m_sockets.begin(), m_sockets.end(), socket));
    socket->deleteLater();
}

void Server::sendResponce(qintptr socketDescriptor, serverResponseType rt, QList<QString> responseParams) {

}


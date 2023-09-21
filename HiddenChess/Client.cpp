#include "Client.h"


Client::Client(QObject *parent)
        : QObject(parent) {
    m_socket = new QTcpSocket;

    connect(m_socket, &QTcpSocket::readyRead, this, &Client::readyRead_slot);
    //connect(m_socket, &QTcpSocket::disconnected, m_socket, &QTcpSocket::deleteLater);

    connect(m_socket, &QTcpSocket::connected, this, [&]() { emit connected_signal(); });
    connect(m_socket, &QTcpSocket::disconnected, m_socket, [&]() { emit clientErr_signal("disconnected"); });
    connect(m_socket, &QTcpSocket::errorOccurred, m_socket, [&]() { emit clientErr_signal("connection error"); });

}

Client::~Client() {}

void Client::SendToServer(QString str) {
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt)
    out << quint16(0) << clientRequestType::chatMess << str;
    out.device()->seek(0);
    out << quint16(m_data.size() - sizeof(quint16));
    m_socket->write(m_data);

}

void Client::connectToHost_slot() {
    if (m_socket->state() == QAbstractSocket::SocketState::ConnectedState)
        return;
    try {
        m_socket->connectToHost("127.0.0.1", 2323);
    }
    catch (...) {
        emit clientErr_signal("programm error");
        return;
    }
    if (m_socket->state() == QAbstractSocket::SocketState::ConnectingState) {
        emit clientErr_signal("connecting...");
    }
}

void Client::tryCreateRoom(QString roomName, QString pswd) {
    if (m_socket->state() != QAbstractSocket::SocketState::ConnectedState) {
        emit clientErr_signal("not connected");
        return;
    }

    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << quint16(0) << clientRequestType::createRoom << roomName << pswd;
    out.device()->seek(0);
    out << quint16(m_data.size() - sizeof(quint16));
    m_socket->write(m_data);


}




void Client::readyRead_slot() {
    QDataStream in(m_socket);

    if (in.status() == QDataStream::Ok) {


        while (true) {
            if (m_nextBlockSize == 0) {
                if (m_socket->bytesAvailable() < 2)
                    break;
                in >> m_nextBlockSize;
            }
            if (m_socket->bytesAvailable() < m_nextBlockSize)
                break;


            serverResponseType rt;
            in >> rt;
            qDebug() << rt;
            if (rt == serverResponseType::roomCreationErr) {
                QString err;
                in >> err;
                emit clientErr_signal(err);
            } else if (rt == serverResponseType::roomCreated) {
                emit roomCreated_signal();
            } else if (rt == serverResponseType::roomNameCheckFailed) {
                emit roomNameUniqNotConfirmed_signal();
            } else if (rt == serverResponseType::roomNameCheckPassed) {
                emit roomNameUniqConfirmed_signal();
            }            else if (rt == serverResponseType::JoiningErrNoRoom){

            }
            else if (rt == serverResponseType::JoiningErrWrongPswd){

            }
            else if (rt == serverResponseType::JoiningErrRoomFull){
            // TODO
            }
            else if (rt == serverResponseType::JoinedToRoom){
                in >> m_currentRoom;
                emit joinedToRoom();
                qDebug()<<"joined to room"<<m_currentRoom;
            }


            m_nextBlockSize = 0;

            break;
        }

    } else
        qDebug() << "read err";
}


void Client::checkRoomNameUniq_slot(QString roomName) {
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << quint16(0) << clientRequestType::checkRoomNameUniq << roomName;
    out.device()->seek(0);
    out << quint16(m_data.size() - sizeof(quint16));
    m_socket->write(m_data);
}

void Client::sendJoiningRequest_slot(QString roomName, QString roomPasswd) {
    qDebug()<<"sendJoiningRequest_slot of Client called";
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << quint16(0) << clientRequestType::tryJoiningToRoom << roomName<< roomPasswd;
    out.device()->seek(0);
    out << quint16(m_data.size() - sizeof(quint16));
    m_socket->write(m_data);
}

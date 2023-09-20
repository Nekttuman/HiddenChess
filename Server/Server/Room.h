#include <QObject>
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>


class Room {
    QTcpSocket *m_hostSocket;
    QTcpSocket *m_oponentSocket;


    QString m_name;
    QString m_pswd;

public:
    Room(QTcpSocket *hostSocket, QString roomName, QString roomPswd) : m_name(roomName), m_pswd(roomPswd) {
        m_hostSocket = hostSocket;
    }

    QString getName() { return m_name; }

    void add_oponent(QTcpSocket *oponentSocket) { m_oponentSocket = oponentSocket; }

};

#pragma once

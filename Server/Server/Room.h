#include <QObject>
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>


class Room {
    QTcpSocket *m_hostSocket;               // replace on socketDescriptor
    QTcpSocket *m_oponentSocket = nullptr;

    QString m_hostNick;
    QString m_opponentNick;


    QString m_name;
    QString m_pswd;

public:
    Room(QTcpSocket *hostSocket, QString roomName, QString roomPswd) : m_name(roomName), m_pswd(roomPswd) {
        m_hostSocket = hostSocket;
    }

    void setHostNick(QString nick){
        m_hostNick = nick;
    }
    QString getHostNick(){return m_hostNick;}

    QTcpSocket* getHostSocket(){
        return m_hostSocket;
    }

    void setOpponentNick(QString nick){
        m_opponentNick = nick;
    }

    QString getName() { return m_name; }
    bool checkPswd(QString pswd){return m_pswd==pswd;}
    bool hasOpponent(){return m_oponentSocket != nullptr;}

    void add_oponent(QTcpSocket *oponentSocket) { m_oponentSocket = oponentSocket; }

    QString getOpponentNick(QTcpSocket *requester){
        if (requester->socketDescriptor() == m_hostSocket->socketDescriptor())
            return m_opponentNick;
        return m_hostNick;
    }

};

#pragma once

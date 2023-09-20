#pragma once

#include <QObject>
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>

#include "Room.h"

enum serverResponcesType {
	roomNameCheckFailed,
	roomNameCheckPassed,
	roomCreated,
	roomCreationErr
};
enum clientRequestType {
	tryConnectToRoom,
	createRoom,
	chatMess,
	move,
	surrenderCommand,
	checkRoomNameUniq
};



class Server : public QTcpServer
{
	Q_OBJECT

public:
	Server();
	~Server();

	QTcpSocket* socket;
	
private:
	QVector<QTcpSocket*> m_sockets;
	quint16 m_nextBlockSize = 0;

	QVector<Room*> m_rooms;

	void SendToClient(QString str);


	void createRoom(QString roomName, QString pswd, QTcpSocket* sender) {

		QByteArray Data;
		QDataStream out(&Data, QIODevice::WriteOnly);
		if (!isUniq(roomName)) {
			out << quint16(0) << serverResponcesType::roomCreationErr<<"Not uniq name";
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

		for (auto room : m_rooms) {
			qDebug() << room->getName();
		}


	}

	void checkRoomNameUniq(QString name, QTcpSocket* sender) {

		QByteArray Data;
		QDataStream out(&Data, QIODevice::WriteOnly);
		if (isUniq(name)) {

			qDebug() << name << "uniq";
			out << quint16(0) << serverResponcesType::roomNameCheckPassed;
			out.device()->seek(0);
			out << quint16(Data.size() - sizeof(quint16));
		}
		else {
			qDebug() << name << "not uniq";
			out << quint16(0) << serverResponcesType::roomNameCheckFailed;
			out.device()->seek(0);
			out << quint16(Data.size() - sizeof(quint16));
		}

		sender->write(Data);
	}

	bool isUniq(QString roomName) {
		for (auto room : m_rooms) {
			if (room->getName() == roomName)
				return false;
		}
		return true;
	}

public slots:
	void incomingConnection(qintptr socketDescriptor) override;
	void slotReadyRead();

private slots:
	void disconnectSocket();
};

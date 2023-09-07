#pragma once

#include <QObject>
#include <QTcpSocket>
#include <qdatastream.h>


enum clientRequestType {
	tryConnectToRoom,
	createRoom,
	chatMess,
	move,
	surrenderCommand
};

enum serverResponceType {
	roomNameCheckFailed,
	roomNameCheckPassed,
	roomCreated,
	roomCreationErr
};



class Client  : public QObject
{
	Q_OBJECT

public:
	Client(QObject *parent);
	~Client();

	void tryCreateRoom(QString roomName, QString pswd) {
		if (socket->state() != QAbstractSocket::SocketState::ConnectedState)
		{
			emit connectionErr_signal("not connected");
			return;
		}
		qDebug() << "try create room";

		Data.clear();
		QDataStream out(&Data, QIODevice::WriteOnly);
		out << quint16(0) << clientRequestType::createRoom << roomName << pswd;
		out.device()->seek(0);
		out << quint16(Data.size() - sizeof(quint16));
		socket->write(Data);


	}

signals:
	void connectionErr_signal(QString);
	void connected_signal();

	void roomNameUniqConfirmed_signal();
	void roomNameUniqNotConfirmed_signal();

public slots:
	void readyRead_slot();
	void connectToHost_slot();

	void checkRoomNameUniq_slot(QString roomName) {
		// TODO
		emit roomNameUniqConfirmed_signal();
	}

private:
	QTcpSocket* socket;
	QByteArray Data;
	quint16 nextBlockSize = 0;

	void SendToServer(QString str);
};

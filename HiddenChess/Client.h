#pragma once

#include <QObject>
#include <QTcpSocket>
#include <qdatastream.h>

class Client  : public QObject
{
	Q_OBJECT

public:
	Client(QObject *parent);
	~Client();

signals:
	void connectionErr(QString);
	void connected_signal();

public slots:
	void readyRead_slot();
	void connectToHost_slot();

private:
	QTcpSocket* socket;
	QByteArray Data;
	quint16 nextBlockSize = 0;

	void SendToServer(QString str);
};

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

//private slots:


signals:
	void connectionErr(QString);

public slots:
	void readyRead_slot();
	void connectToHost_slot();

private:
	QTcpSocket* socket;
	QByteArray Data;
	quint16 nextBlockSize = 0;

	void SendToServer(QString str);
};

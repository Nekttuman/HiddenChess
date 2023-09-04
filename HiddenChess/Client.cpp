#include "Client.h"


Client::Client(QObject* parent)
	: QObject(parent)
{
	socket = new QTcpSocket;

	connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead_slot);
	connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

	connect(socket, &QTcpSocket::connected, this, [&]() {emit connected_signal(); });
	connect(socket, &QTcpSocket::disconnected, socket, [&]() {emit connectionErr("disconnected"); });
	connect(socket, &QTcpSocket::errorOccurred, socket, [&]() {emit connectionErr("connection error"); });

}

Client::~Client()
{}

void Client::SendToServer(QString str)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	//out.setVersion(QDataStream::Qt)
	out << quint16(0) << str;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));
	socket->write(Data);

}

void Client::connectToHost_slot(){
	try {
		//qDebug() << "connecting to host";
		
		socket->connectToHost("127.0.0.1", 2323);
	}
	catch (...) {
		//qDebug() << "read err";
		emit connectionErr("programm error");
		return;
	}
	if (socket->state() == QAbstractSocket::SocketState::ConnectingState) {
		emit connectionErr("connecting...");
	}


	//emit connectionErr("err");
}

//void Client::on_connectButton_clicked() {
//	socket->connectToHost("127.0.0.1", 2323);
//}
//
//void Client::on_sendButton_clicked() {
//	if (ui.lineEdit->text() == "")
//		return;
//	SendToServer(ui.lineEdit->text());
//}

void Client::readyRead_slot() {
	QDataStream in(socket);

	//in.setVersion(QDataStream::Qt_6_2);

	if (in.status() == QDataStream::Ok) {
		//QString str;
		//in >> str;
		//ui.textBrowser->append(str);


		QString str;
		while (true) {
			if (nextBlockSize == 0) {
				if (socket->bytesAvailable() < 2)
					break;
				in >> nextBlockSize;
			}
			if (socket->bytesAvailable() < nextBlockSize)
				break;

			in >> str;
			nextBlockSize = 0;
			qDebug()<<str;

			break;
		}

	}
	else
		qDebug()<<"read err";
}
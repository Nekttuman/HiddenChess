#include "Client.h"


Client::Client(QObject* parent)
	: QObject(parent)
{
	socket = new QTcpSocket;

	connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead_slot);
	//connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

	connect(socket, &QTcpSocket::connected, this, [&]() {emit connected_signal(); });
	connect(socket, &QTcpSocket::disconnected, socket, [&]() {emit connectionErr_signal("disconnected"); });
	connect(socket, &QTcpSocket::errorOccurred, socket, [&]() {emit connectionErr_signal("connection error"); });

}

Client::~Client()
{}

void Client::SendToServer(QString str)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	//out.setVersion(QDataStream::Qt)
	out << quint16(0) << clientRequestType::chatMess << str;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));
	socket->write(Data);

}

void Client::connectToHost_slot(){
	if (socket->state() == QAbstractSocket::SocketState::ConnectedState)
		return;
	try {
		socket->connectToHost("127.0.0.1", 2323);
	}
	catch (...) {
		emit connectionErr_signal("programm error");
		return;
	}
	if (socket->state() == QAbstractSocket::SocketState::ConnectingState) {
		emit connectionErr_signal("connecting...");
	}
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

	if (in.status() == QDataStream::Ok) {


		while (true) {
			if (nextBlockSize == 0) {
				if (socket->bytesAvailable() < 2)
					break;
				in >> nextBlockSize;
			}
			if (socket->bytesAvailable() < nextBlockSize)
				break;


			serverResponceType rt;
			in >> rt;
			if (rt == serverResponceType::roomCreationErr) {

			}
			else if (rt == serverResponceType::roomCreated) {
				
			}
			else if (rt == serverResponceType::roomNameCheckFailed) {
				emit roomNameUniqNotConfirmed_signal();
			}
			else if (rt == serverResponceType::roomNameCheckPassed) {
				emit roomNameUniqConfirmed_signal();
			}


			nextBlockSize = 0;

			break;
		}

	}
	else
		qDebug()<<"read err";
}
#include "ChatWidget.h"

ChatWidget::ChatWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket;

	connect(socket, &QTcpSocket::readyRead, this, &ChatWidget::slotReadyRead);
	connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

ChatWidget::~ChatWidget()
{}

void ChatWidget::SendToServer(QString str)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	//out.setVersion(QDataStream::Qt)
	out <<quint16(0)<< str;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));
	socket->write(Data);

	ui.textEdit->clear();
}

void ChatWidget::on_connectButton_clicked() {
	socket->connectToHost("127.0.0.1", 2323);
}

void ChatWidget::on_sendButton_clicked() {
	//SendToServer(ui.textEdit->);
}

void ChatWidget::slotReadyRead() {
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
			ui.textBrowser->append(str);
			
			break;
		}

	}
	else
		ui.textBrowser->append("read err");
}

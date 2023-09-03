#pragma once

#include <QtWidgets>
#include <QTcpSocket>
#include "ui_ChatWidget.h"

class ChatWidget : public QWidget
{
	Q_OBJECT

public:
	ChatWidget(QWidget *parent = nullptr);
	~ChatWidget();

private slots:
	void on_connectButton_clicked();
	void on_sendButton_clicked();

public slots:
	void slotReadyRead();

private:
	Ui::ChatWidgetClass ui;
	QTcpSocket* socket;
	QByteArray Data;
	quint16 nextBlockSize = 0;

	void SendToServer(QString str);
};

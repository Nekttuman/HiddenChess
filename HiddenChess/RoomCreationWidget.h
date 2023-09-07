#pragma once

#include <QtWidgets>
#include "ui_RoomCreationWidget.h"

class RoomCreationWidget : public QWidget
{
	Q_OBJECT

public:
	RoomCreationWidget(QWidget *parent = nullptr);
	~RoomCreationWidget();

	void disableCreateRoomBtn() {
		ui.createRoomButton->setDisabled(true);
	}

	void enableCreateRoomBtn() {
		ui.createRoomButton->setDisabled(false);
	}

	QString getRoomName() {
		return ui.roomNameLineEdit->text();
	}
	QString getPswd() {
		return ui.pswdLineEdit->text();
	}
private:
	Ui::RoomCreationWidgetClass ui;

	bool roomNameUniq = false;

signals:
	void backToMenu_signal();
	void createRoom_signal();
	void fieldsCorrect_signal();
	void checkRoomNameUniquness_signal(QString);

private slots:
	void emitBackToMenu_slot() {
		emit backToMenu_signal();
	}
	void createRoom_slot() {
		emit createRoom_signal();
	}

	void validateFields_slot() {
		bool isValid = true;

		if (ui.pswdLineEdit->text() == ""
			|| ui.pswdLineEdit->text().contains(" ")) 
		{
			ui.roomPswdErrorLabel->show();
			isValid = false;
		} else {
			ui.roomPswdErrorLabel->hide();
		}

		if (ui.roomNameLineEdit->text() == ""
			|| ui.roomNameLineEdit->text().contains(" ")) 
		{
			ui.roomNameErrorLabel->show();
			ui.roomNameErrorLabel->setText("name err");
			isValid = false;		
		} else {
			ui.roomNameErrorLabel->hide();
			emit checkRoomNameUniquness_signal(ui.roomNameLineEdit->text());
		}

		if (isValid)
			emit fieldsCorrect_signal();
	}

public slots:

	void roomNameUniqConfirmed_slot() {
		qDebug() << "sh";
		roomNameUniq = true;

		ui.roomNameErrorLabel->hide();
		
	}
	void roomNameUniqNotConfirmed_slot() {
		roomNameUniq = false;

		ui.roomNameErrorLabel->setText("name already exists");
		ui.roomNameErrorLabel->show();
	}

	void allowRoomCreation_slot() {
		if (roomNameUniq) {
			ui.createRoomButton->setEnabled(true);
		}
	}


};

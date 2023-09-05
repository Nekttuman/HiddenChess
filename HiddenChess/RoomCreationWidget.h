#pragma once

#include <QWidget>
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

private:
	Ui::RoomCreationWidgetClass ui;

signals:
	void backToMenu_signal();
	void startGame_signal();
	void fieldsCorrect_signal();

private slots:
	void emitBackToMenu_slot() {
		emit backToMenu_signal();
	}
	void emitStartGame_slot() {
		emit startGame_signal();
	}

	void validateFields_slot() {
		// not check room name uniqueness, it does HiddenChess class
		bool isValid = true;

		if (ui.pswdLineEdit->text() == ""
			|| ui.pswdLineEdit->text().contains(" ")) 
			ui.roomPswdErrorLabel->show();
		else {
			ui.roomPswdErrorLabel->hide();
			isValid = false;
		}
		if (ui.roomNameLineEdit->text() == ""
			|| ui.roomNameLineEdit->text().contains(" "))
			ui.roomNameErrorLabel->show();
		else {
			ui.roomNameErrorLabel->hide();
			isValid = false;
		}

		if (isValid)
			emit fieldsCorrect_signal();
	}
};

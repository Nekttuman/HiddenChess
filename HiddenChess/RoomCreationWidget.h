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

private slots:
	void emitBackToMenu_slot() {
		emit backToMenu_signal();
	}
	void emitStartGame_slot() {
		emit startGame_signal();
	}
};

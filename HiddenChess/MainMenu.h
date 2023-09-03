#pragma once

#include <QWidget>
#include "ui_MainMenu.h"

class MainMenu : public QWidget
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = nullptr);
	~MainMenu();

private:
	Ui::MainMenuClass ui;



signals:
	void createRoomBtn_signal();
	void joinRoomBtn_signal();

	void exitBtn_signal();

private slots:
	void emitCreateRoom_signal() {
		emit createRoomBtn_signal();
	}
	void emitJoinBtn_signal() {
		emit joinRoomBtn_signal();
	}
	void emitExit_signal(){
		emit exitBtn_signal();
	}

			
};

//
//QObject::connect(&a, SIGNAL(valueChanged(int)),
//	&b, SLOT(setValue(int)));
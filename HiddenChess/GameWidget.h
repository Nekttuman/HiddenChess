#pragma once

#include <QtWidgets>
#include "ui_GameWidget.h"
#include "Square.h"

class GameWidget : public QWidget
{
	Q_OBJECT


public:
	Square* squares[8][8];

public:
	GameWidget(QWidget *parent = nullptr);
	~GameWidget();


private:
	Ui::GameWidgetClass ui;


	void setField();
	void setFigures();
signals:
	void backToMenu_signal();

private slots:
	void emitBackToMenu_slot() {
		emit backToMenu_signal();
	}






private slots:
	void startGame_slot();

protected:

	//void paintEvent(QPaintEvent* event) override;
};




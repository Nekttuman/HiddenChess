#pragma once

#include <QtWidgets>
#include "ui_GameWidget.h"

class GameWidget : public QWidget
{
	Q_OBJECT

public:
	GameWidget(QWidget *parent = nullptr);
	~GameWidget();

private:
	Ui::GameWidgetClass ui;

signals:
	void backToMenu_signal();

private slots:
	void emitBackToMenu_slot() {
		emit backToMenu_signal();
	}
};




class Square : public QWidget {
public:
	Square(QWidget* parent = nullptr, int color = 0) : QWidget(parent), m_color(color) {

	}
	~Square() {}


protected:
	bool m_color = 0;

	void paintEvent(QPaintEvent* pe) {
		if (m_color)
			this->setStyleSheet("background-color:rgb(0,0,0);");

	}
};
#pragma once

#include <QWidget>
#include "ui_Square.h"

class Square : public QWidget
{
	Q_OBJECT

public:
	Square(QWidget *parent = nullptr);
	~Square();
	Square(int x, int y, QWidget* parent = nullptr);

public:

	QColor bgcolor = Qt::black;
	QPoint x, y;

private:
	Ui::SquareClass ui;


protected:
	void paintEvent(QPaintEvent* event) override;
};

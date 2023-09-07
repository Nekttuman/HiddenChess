#pragma once

#include <QtWidgets>
#include <qlabel.h>
#include "ui_Square.h"


enum FigureType {
	no,
	pawn,

};

class ImgManager {
public:

	QPixmap pawnImg;


	ImgManager() {
		pawnImg.fill(Qt::transparent);
		pawnImg.load("../HiddenChess/Figures/pawnWhite.png");
	}
};

class Square : public QWidget
{
	Q_OBJECT

public:
	~Square();
	Square(int x, int y, QWidget* parent = nullptr);

	

	void setFigureType(FigureType figureType, QPixmap& img);

public:

	QColor bgcolor = Qt::black;
	QPoint x, y;
	QPixmap *image;
	FigureType ft;

private:
	Ui::SquareClass ui;



protected:
	void paintEvent(QPaintEvent* event) override;
};

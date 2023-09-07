#include "Square.h"
#include <qpainter.h>
#include <qdebug.h>



Square::~Square()
{}


Square::Square(int x, int y, QWidget* parent) {

	ui.setupUi(this);
	if ((x + y) % 2 == 0) {

		bgcolor = Qt::black;

	}
	else bgcolor = Qt::white;

}


void Square::paintEvent(QPaintEvent* event) {

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(bgcolor);
	painter.drawRect(rect());


	switch (ft) {
	case FigureType::pawn:
		painter.drawPixmap(rect(), *image);
		break;


	}
};


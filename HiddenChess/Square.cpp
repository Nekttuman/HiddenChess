#include "Square.h"
#include <qpainter.h>

Square::Square(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Square::~Square()
{}



void Square::paintEvent(QPaintEvent* event) {

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(bgcolor);
	painter.drawRect(rect());

};


Square::Square(int x, int y, QWidget* parent) {

	if ((x + y) % 2 == 0) {

		bgcolor = Qt::black;

	}
	else bgcolor = Qt::white;


}
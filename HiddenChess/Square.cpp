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

	QPixmap image = "image2.png";
	this->setAutoFillBackground(true);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	//painter.setBackgroundMode();
	painter.setBrush(bgcolor);
	painter.drawRect(rect());
	painter.drawPixmap(rect(), image);

};


Square::Square(int x, int y, QWidget* parent) {


	if ((x + y) % 2 == 0) {

		bgcolor = Qt::black;

	}
	else bgcolor = Qt::white;


}
#include "Square.h"
#include <qpainter.h>
#include <qdebug.h>
#include "MyFunc.h"
#include "GameWidget.h"



Square::~Square()
{}


Square::Square(int x_, int y_, QWidget* parent) {

	ui.setupUi(this);
	ui.label->acceptDrops();
	this->setAcceptDrops(true);
	ui.label->setAcceptDrops(false);

	x = x_;
	y = y_;

	if ((x_ + y_) % 2 == 0) {

		bgcolor = Qt::black;

	}
	else bgcolor = Qt::white;
	
}


void Square::paintEvent(QPaintEvent* event) {

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(bgcolor);
	painter.drawRect(rect());
	ui.label->setFixedSize(this->size());

	
	
};

void Square::setFigureType(Ft figure_, Fc color_) {


	Ffigure = new Figure(figure_, color_);
	image = QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio);

	ui.label->setPixmap(image);
}




void Square::mousePressEvent(QMouseEvent* event) {

	if ((Ffigure!=nullptr)) {


		qDebug() << "signal";
		emit showMoves_signal(Ffigure, x, y);


		ui.label->setPixmap(QPixmap());

		QDrag* drag = new QDrag(this);
		QMimeData* mimeData = new QMimeData;
		QByteArray data = serialize();

		

		mimeData->setData("application/Figure", data);

		drag->setMimeData(mimeData);
		drag->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio));
		Ffigure = nullptr;

		drag->setHotSpot(event->pos() - this->rect().topLeft());

		Qt::DropAction dropAction = drag->exec();

	}
	
}


void Square::dropEvent(QDropEvent* event) {

	const QMimeData* mimeData = event->mimeData();
	

	if (mimeData->hasFormat("application/Figure")) {

		
		QByteArray data = event->mimeData()->data("application/Figure");
		
		Ffigure = deserialize(data);

		ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio));
	}

	
	event->acceptProposedAction();
}

void Square::dragEnterEvent(QDragEnterEvent* event) {
	const QMimeData* mimeData = event->mimeData();
	
		event->acceptProposedAction();
}




QByteArray Square::serialize() {

	QByteArray data;
	QDataStream stream(&data, QIODevice::WriteOnly);
	qintptr objAddress = reinterpret_cast<qintptr>(Ffigure);

	stream << objAddress;
	
	return data;
}




Figure* Square::deserialize(QByteArray data) {

	QDataStream stream(data);
	qintptr	objAdress;

	stream >> objAdress;


	Figure* obj = reinterpret_cast<Figure*>(objAdress);

	return obj;

}
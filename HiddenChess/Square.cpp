#include "Square.h"
#include <qpainter.h>
#include <qdebug.h>
#include "MyFunc.h"



Square::~Square()
{}


Square::Square(int x, int y, QWidget* parent) {

	ui.setupUi(this);
	ui.label->acceptDrops();
	this->setAcceptDrops(true);
	ui.label->setAcceptDrops(false);
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
	ui.label->setFixedSize(this->size());

	
	
};

void Square::setFigureType(FigureType figureType, QPixmap& img) {
	ft = figureType;
	image = img.scaled(this->size(), Qt::KeepAspectRatio);
	ui.label->setPixmap(image);
}




void Square::mousePressEvent(QMouseEvent* event) {

	if (!image.isNull()) {

		ui.label->setPixmap(QPixmap());

		QDrag* drag = new QDrag(this);
		QMimeData* mimeData = new QMimeData;

		mimeData->setImageData(image);
		drag->setMimeData(mimeData);
		drag->setPixmap(image);

		image = QPixmap();


		drag->setHotSpot(event->pos() - this->rect().topLeft());

		Qt::DropAction dropAction = drag->exec();

	}
	
}


void Square::dropEvent(QDropEvent* event) {

	const QMimeData* mimeData = event->mimeData();
	

	if (mimeData->hasImage()) {
		// Retrieve the dropped image from the mime data
		QPixmap droppedImage = qvariant_cast<QPixmap>(mimeData->imageData());

		// Handle the dropped image as needed
		// You can display it or perform other operations
		image = droppedImage;
		// For example, if you want to display the image in your QLabel (ui.label),
		// you can set the pixmap like this:
		ui.label->setPixmap(droppedImage);
		
	}
	
	event->acceptProposedAction();
}

void Square::dragEnterEvent(QDragEnterEvent* event) {
	const QMimeData* mimeData = event->mimeData();
	

	if (mimeData->hasImage()) {
		event->acceptProposedAction();
	}
}
#include "Square.h"
#include <qpainter.h>
#include <qdebug.h>
#include "MyFunc.h"


Square::~Square() {}


Square::Square(int x_, int y_, QWidget *parent) {

    ui.setupUi(this);
    ui.label->acceptDrops();
    this->setAcceptDrops(true);
    ui.label->setAcceptDrops(false);

    x = x_;
    y = y_;

    if ((x_ + y_) % 2 == 0) {

        bgcolor = Qt::black;

    } else bgcolor = Qt::white;

}


void Square::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(bgcolor);
    painter.drawRect(rect());
    ui.label->setFixedSize(this->size());
    painter.end();
};


void Square::setFigureType(Ft figure_, Fc color_) {



    Ffigure = new Figure(figure_, color_);
    

    ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio));
}


void Square::mousePressEvent(QMouseEvent *event) {

    if ((Ffigure != nullptr)) {


        
        emit showMoves_signal(Ffigure, x, y);


        ui.label->setPixmap(QPixmap());

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
        QByteArray data = serialize();


        mimeData->setData("application/Figure", data);

        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio));
        Ffigure = nullptr;

        drag->setHotSpot(event->pos() - this->rect().topLeft());

        Qt::DropAction dropAction = drag->exec();
        emit hideMoves_signal(Ffigure, x, y);
    }

}


void Square::dropEvent(QDropEvent *event) {

    const QMimeData *mimeData = event->mimeData();


    if (mimeData->hasFormat("application/Figure")) {


        QByteArray data = event->mimeData()->data("application/Figure");

        Ffigure = deserialize(data);

        ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio));
    }


    event->acceptProposedAction();
}

void Square::dragEnterEvent(QDragEnterEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    
    event->acceptProposedAction();
}


QByteArray Square::serialize() {

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    qintptr objAddress = reinterpret_cast<qintptr>(Ffigure);

    stream << objAddress;

    return data;
}


Figure *Square::deserialize(QByteArray data) {

    QDataStream stream(data);
    qintptr objAdress;

    stream >> objAdress;


    Figure *obj = reinterpret_cast<Figure *>(objAdress);

    return obj;

}


void Square::lightSquare() {


	if (Ffigure == nullptr) {
		ui.label->setPixmap(QPixmap(":/HiddenChess/AnotherPics/green.png").scaled(this->size(), Qt::IgnoreAspectRatio));
	}

  if (Ffigure != nullptr) {
    QPixmap greenPixmap(":/HiddenChess/AnotherPics/green.png");
    greenPixmap = greenPixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    
    QPixmap currentPixmap = ui.label->pixmap()->scaled(this->size(), Qt::IgnoreAspectRatio);

    QPixmap resultPixmap(this->size());
    resultPixmap.fill(Qt::transparent);

    QPainter painter(&resultPixmap);
    painter.drawPixmap(0, 0, currentPixmap);
    painter.drawPixmap(0, 0, greenPixmap);
    painter.end();

    ui.label->setPixmap(resultPixmap);
  }


}


void Square::hideSquare() {


  if (Ffigure == nullptr) ui.label->setPixmap(QPixmap(""));
  else ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio));
	
}
#include "Square.h"
#include <qpainter.h>
#include <qdebug.h>
#include "MyFunc.h"
#include "DnData.h";
#include "qmath.h"


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
    

    ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio));
}


void Square::mousePressEvent(QMouseEvent *event) {
    
    if ((Ffigure != nullptr) && Ffigure->fColor==player) {

        emit showMoves_signal(Ffigure, x, y);

        ui.label->setPixmap(QPixmap());

        DnData dndata = DnData(Ffigure, x, y);

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
        QByteArray data = serialize(&dndata);


        mimeData->setData("application/Figure", data);
        drag->setMimeData(mimeData);

        auto image = QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio);
        drag->setPixmap(image);

        QPoint hotSpot = QPoint(image.size().width() / 2, image.size().height() / 2);
        drag->setHotSpot(hotSpot);

        Qt::DropAction dropAction = drag->exec();

        if (dropAction == Qt::IgnoreAction) {

          ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio));
        }
        else Ffigure = nullptr;

        emit hideMoves_signal(Ffigure, x, y);
        
    }

}


void Square::dragEnterEvent(QDragEnterEvent* event) {
  const QMimeData* mimeData = event->mimeData();


  if (Ffigure == nullptr) event->acceptProposedAction();
  else if (Ffigure->fColor == enemy)event->acceptProposedAction();
  else if (Ffigure->fColor == player) {
   
    event->setDropAction(Qt::IgnoreAction); 
    event->accept();
  }
}


void Square::dropEvent(QDropEvent *event) {

    const QMimeData *mimeData = event->mimeData();

    event->acceptProposedAction();

    QByteArray data = event->mimeData()->data("application/Figure");
    DnData* dndata = deserialize(data);

    if (dndata->Ffigure->figureType == king && dndata->Ffigure->FirstMoveDone == false 
          && abs(dndata->prevPos.y() - y) == 2) {

        if (dndata->prevPos.y() - y == 2) {
          qDebug() << "rakirovka";
          emit relocateLeftRook_signal(dndata->prevPos.x(), dndata->prevPos.y());
        }
        else {
          qDebug() << "rakirovka";
          emit relocateRightRook_signal(dndata->prevPos.x(), dndata->prevPos.y());
        }
        Ffigure = dndata->Ffigure;
        ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio));
        Ffigure->FirstMoveDone = true;
      

    }

    else if (Ffigure==nullptr) {



       Ffigure = dndata->Ffigure;
       ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio));
       Ffigure->FirstMoveDone = true;



    }
    else if (Ffigure->fColor == enemy) {

      Ffigure = dndata->Ffigure;
      ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::KeepAspectRatio));
      Ffigure->FirstMoveDone = true;

    }

    if (Ffigure->fakeStatus==false && !Ffigure->availableMoves.contains(QPoint(x, y))) {
      Ffigure->fakeStatus = true;
      qDebug() << "fake";
    }
    Ffigure->availableMoves.clear();
}


QByteArray Square::serialize(DnData* dndata) {

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    qintptr objAddress = reinterpret_cast<qintptr>(dndata);

    stream << objAddress;

    return data;
}


DnData *Square::deserialize(QByteArray data) {

    QDataStream stream(data);
    qintptr objAdress;

    stream >> objAdress;


    DnData* obj = reinterpret_cast<DnData*>(objAdress);

    return obj;

}


void Square::lightSquare() {


	if (Ffigure == nullptr) {
		ui.label->setPixmap(QPixmap(":/HiddenChess/AnotherPics/green.png").scaled(this->size(), Qt::IgnoreAspectRatio));
	}

  else {

    QPixmap greenPixmap(":/HiddenChess/AnotherPics/red.png");
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

void Square::resizePicture() {

  if (Ffigure != nullptr) ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio));
}


void Square::deleteFigure() {
  Ffigure = nullptr;
  ui.label->setPixmap(QPixmap(""));
}


void Square::placeFigure(Figure* figure) {

  Ffigure = figure;
  ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio));


}
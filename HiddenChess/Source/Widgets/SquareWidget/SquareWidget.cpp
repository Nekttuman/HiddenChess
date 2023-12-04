#include "SquareWidget.h"
#include <qpainter.h>
#include <qdebug.h>
#include "Figure.h"
#include "qmath.h"


SquareWidget::~SquareWidget() {}


SquareWidget::SquareWidget(int x_, int y_, QWidget *parent) {

    ui.setupUi(this);
    ui.label->acceptDrops();
    this->setAcceptDrops(true);

    x = x_;
    y = y_;

    if ((x_ + y_) % 2 == 0) {

        bgcolor = Qt::black;

    } else bgcolor = Qt::white;

}


void SquareWidget::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(bgcolor);
    painter.drawRect(rect());
    ui.label->setFixedSize(this->size());
    painter.end();
};


void SquareWidget::setFigureType(Ft figure_, PlayerType type, FigureColor color) {

    Ffigure = new Figure(figure_, type, color);


    ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio));
}


void SquareWidget::lightSquare() {


    if (Ffigure == nullptr) {
        ui.label->setPixmap(QPixmap(":/MainWindow/AnotherPics/green.png").scaled(this->size(), Qt::IgnoreAspectRatio));
    } else {

        QPixmap greenPixmap(":/MainWindow/AnotherPics/red.png");
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


void SquareWidget::hideSquare() {


    if (Ffigure == nullptr) ui.label->setPixmap(QPixmap(""));
    else ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio));

}

void SquareWidget::resizePicture() {

    if (Ffigure != nullptr)
        ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio));
}


void SquareWidget::deleteFigure() {
    if (Ffigure != nullptr) {
        delete Ffigure;
        Ffigure = nullptr;
    }
    ui.label->setPixmap(QPixmap(""));
}


void SquareWidget::removeFigure() {
    Ffigure = nullptr;
    ui.label->setPixmap(QPixmap(""));
}


void SquareWidget::placeFigure(Figure *figure) {
    if (Ffigure!=nullptr)
        delete Ffigure;

    Ffigure = figure;
    Ffigure->FirstMoveDone = true;
    ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio));
}


void SquareWidget::mousePressEvent(QMouseEvent *event) {


    if ((Ffigure != nullptr) && Ffigure->playerType == player) {

        emit showMoves_signal(Ffigure, x, y);

        ui.label->setPixmap(QPixmap(""));

        QDrag *drag = new QDrag(this);

        QMimeData *mimeData = new QMimeData;

        QByteArray data;
        QDataStream dataStream(&data, QIODevice::WriteOnly);
        dataStream << x << y;

        mimeData->setData("application/Move", data);

        drag->setMimeData(mimeData);


        auto image = QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio);
        drag->setPixmap(image);

        QPoint hotSpot = QPoint(image.size().width() / 2, image.size().height() / 2);
        drag->setHotSpot(hotSpot);

        Qt::DropAction dropAction = drag->exec();

        if (dropAction == Qt::IgnoreAction) {
            qDebug() << "ignoreAction";
            ui.label->setPixmap(QPixmap(Ffigure->figureImage).scaled(this->size(), Qt::IgnoreAspectRatio));
        }

        emit hideMoves_signal();

    }

}


void SquareWidget::dragEnterEvent(QDragEnterEvent *event) {
    const QMimeData *mimeData = event->mimeData();

    event->acceptProposedAction();
}


void SquareWidget::dropEvent(QDropEvent *event) {

    int prevX, prevY;
    event->acceptProposedAction();
    QByteArray data = event->mimeData()->data("application/Move");

    QDataStream dataStream(&data, QIODevice::ReadOnly);
    dataStream >> prevX >> prevY;

    qDebug() << "from" << QString::number(prevX) << QString::number(prevY) << "to"
             << QString::number(x) << QString::number(y);

    emit moveRequest_signal(prevX, prevY, x, y, event);


}

void SquareWidget::YaDolbaebVcelenskogoMashtaba() {
    Ffigure = nullptr;
    ui.label->setPixmap(QPixmap(""));

}
#pragma once

#include <QtWidgets>
#include <qdrag.h>
#include <qlabel.h>
#include "ui_Square.h"
#include "MyFunc.h"



class Square : public QWidget {
Q_OBJECT

public:
    ~Square();

    Square(int x, int y, QWidget *parent = nullptr);

    void setFigureType(Ft figure_, Fc color_);
    void lightSquare();
    void hideSquare();
    void resizePicture();
    void deleteFigure();
    void placeFigure(Figure* figure);
    void removeFigure();


public:

    QColor bgcolor = Qt::black;
    int x, y;
    Figure* Ffigure = nullptr;

signals:

    void showMoves_signal(Figure *figure, int x, int y);
    void hideMoves_signal();
    void moveRequest_signal(int prevX, int prevY, int x, int y, QDropEvent* event);

private:
    Ui::SquareClass ui;


protected:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override; 
    void dropEvent(QDropEvent *event) override;
};

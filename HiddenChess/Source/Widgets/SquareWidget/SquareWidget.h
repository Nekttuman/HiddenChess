#pragma once

#include <QtWidgets>
#include <qdrag.h>
#include <qlabel.h>
#include "ui_SquareWidget.h"
#include "Figure.h"


class SquareWidget : public QWidget {
Q_OBJECT

public:
    ~SquareWidget();

    SquareWidget(int x, int y, QWidget *parent = nullptr);

    void setFigureType(Ft figure_, PlayerType type, FigureColor color);

    void lightSquare();

    void hideSquare();

    void resizePicture();

    void deleteFigure();

    void placeFigureWithHack(Figure *figure);

    void placeFigureWithoutHack(Figure *figure);

    void removeFigure();


public:

    QColor bgcolor = Qt::black;
    int x, y;
    Figure *Ffigure = nullptr;

signals:

    void showMoves_signal(Figure *figure, int x, int y);

    void hideMoves_signal();

    void moveRequest_signal(int prevX, int prevY, int x, int y, QDropEvent *event);

private:
    Ui::SquareClass ui;
    void YaDolbaebVcelenskogoMashtaba();

protected:

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dropEvent(QDropEvent *event) override;
};

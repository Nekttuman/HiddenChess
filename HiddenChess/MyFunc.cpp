#include <QCoreApplication>
#include <QCursor>
#include <QMouseEvent>
#include <QThread>
#include <QApplication>
#include <Windows.h>
#include <qdebug.h>
#include "MyFunc.h"

void hideCursorMe() {
    qDebug() << "yeah";
    ShowCursor(FALSE);

}

void showCursorMe() {
    ShowCursor(TRUE);
}


Figure::Figure(Ft figure_, Fc fcolor_) {

	figure = figure_;
	fColor = fcolor_;
	fakeStatus = false;
	figureImage = FigureImages[{figure_, fcolor_}];

};





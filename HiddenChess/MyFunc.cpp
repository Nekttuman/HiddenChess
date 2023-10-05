#include <QCursor>
#include <Windows.h>
#include "MyFunc.h"

void hideCursorMe() {
    qDebug() << "yeah";
    ShowCursor(FALSE);

}

void showCursorMe() {
    ShowCursor(TRUE);
}


Figure::Figure(Ft figure_, Fc fcolor_) {

    figureType = figure_;
    fColor = fcolor_;
    fakeStatus = false;
    figureImage = FigureImages[{figure_, fcolor_}];

};





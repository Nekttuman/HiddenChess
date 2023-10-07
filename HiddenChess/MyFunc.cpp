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


Figure::Figure(Ft figure_, PlayerType type, Fc color) {

    figureType = figure_;
    playerType = type;
    fakeStatus = false;
    figureImage = FigureImages[{figure_, color}];

    if (figureType == king || figureType == rook) FirstMoveDone = false;
    else FirstMoveDone = true;

};





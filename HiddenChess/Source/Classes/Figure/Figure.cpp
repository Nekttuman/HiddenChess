#include <QCursor>
#include <Windows.h>
#include "Figure.h"

void hideCursorMe() {
    qDebug() << "yeah";
    ShowCursor(FALSE);

}

void showCursorMe() {
    ShowCursor(TRUE);
}


Figure::Figure(Ft figure_, PlayerType type, FigureColor color) {

    figureType = figure_;
    playerType = type;
    fakeStatus = false;
    figureImage = FigureImages[{figure_, color}];

    if (figureType == king || figureType == rook) FirstMoveDone = false;
    else FirstMoveDone = true;

};

Ft getKeyByValue(const QMap<Ft, std::string>& map, std::string& value) {
    for (auto it = map.begin(); it != map.end(); ++it) {
        if (it.value() == value) {
            return it.key();
        }
    }
}



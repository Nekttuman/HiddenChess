#pragma once

#include <QtWidgets>
#include <qmap.h>
#include<qstring.h>
#include <QList>
#include <tuple>


const int knightMoves[8][2] = {
        {1, 2},
        {2, 1},
        {2, -1},
        {1, -2},
        {-1, -2},
        {-2, -1},
        {-2, 1},
        {-1, 2}
};

enum Ft {
    pawn,
    king,
    queen,
    rook,
    knight,
    bishop
};
enum Fc {
    player, enemy
};

typedef std::tuple<Ft, Fc> TwoKey;
typedef QList<QList<int>> TwoDimIntArray;

const QMap<TwoKey, QString> FigureImages = 
{{{pawn,   player}, (":/HiddenChess/Figures/Wp.png")},
{{pawn,   enemy}, (":/HiddenChess/Figures/Bp.png")},
{{king,   player}, (":/HiddenChess/Figures/Wk.png")},
{{king,   enemy}, (":/HiddenChess/Figures/Bk.png")},
{{queen,  player}, (":/HiddenChess/Figures/Wq.png")},
{{queen,  enemy}, (":/HiddenChess/Figures/Bq.png")},
{{rook,   player}, (":/HiddenChess/Figures/Wr.png")},
{{rook,   enemy}, (":/HiddenChess/Figures/Br.png")},
{{knight, player}, (":/HiddenChess/Figures/Wn.png")},
{{knight, enemy}, (":/HiddenChess/Figures/Bn.png")},
{{bishop, player}, (":/HiddenChess/Figures/Wb.png")},
{{bishop, enemy}, (":/HiddenChess/Figures/Bb.png")}
};


class Figure {

public:

    Ft figureType;
    Fc fColor;
    QString figureImage = "";
    bool fakeStatus;
    QList<QPoint> availableMoves;

    Figure(Ft figure_, Fc fcolor_);

    bool FirstMoveDone;

private:


};







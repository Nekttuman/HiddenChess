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
enum PlayerType {
    player, enemy
};

enum Fc {
  white, black
};

typedef std::tuple<Ft, Fc> TwoKey;
typedef QList<QList<int>> TwoDimIntArray;

const QMap<TwoKey, QString> FigureImages = 
{{{pawn,   white}, (":/HiddenChess/Figures/Wp.png")},
{{pawn,   black}, (":/HiddenChess/Figures/Bp.png")},
{{king,   white}, (":/HiddenChess/Figures/Wk.png")},
{{king,   black}, (":/HiddenChess/Figures/Bk.png")},
{{queen,  white}, (":/HiddenChess/Figures/Wq.png")},
{{queen,  black}, (":/HiddenChess/Figures/Bq.png")},
{{rook,   white}, (":/HiddenChess/Figures/Wr.png")},
{{rook,   black}, (":/HiddenChess/Figures/Br.png")},
{{knight, white}, (":/HiddenChess/Figures/Wn.png")},
{{knight, black}, (":/HiddenChess/Figures/Bn.png")},
{{bishop, white}, (":/HiddenChess/Figures/Wb.png")},
{{bishop, black}, (":/HiddenChess/Figures/Bb.png")}
};


class Figure {

public:

    Ft figureType;
    PlayerType playerType;
    QString figureImage = "";
    bool fakeStatus;
    QList<QPoint> availableMoves;

    Figure(Ft figure_, PlayerType fcolor_, Fc color_);

    bool FirstMoveDone;

    ~Figure(){

      qDebug() << "ia umer";
    }

private:


};







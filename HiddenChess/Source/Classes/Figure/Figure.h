#pragma once

#include <QtWidgets>
#include <qmap.h>
#include<qstring.h>
#include <QList>
#include <tuple>


const int knightMoves[8][2] = {
        {1,  2},
        {2,  1},
        {2,  -1},
        {1,  -2},
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
        {{{pawn,   white}, (":/MainWindow/Figures/Wp.png")},
         {{pawn,   black}, (":/MainWindow/Figures/Bp.png")},
         {{king,   white}, (":/MainWindow/Figures/Wk.png")},
         {{king,   black}, (":/MainWindow/Figures/Bk.png")},
         {{queen,  white}, (":/MainWindow/Figures/Wq.png")},
         {{queen,  black}, (":/MainWindow/Figures/Bq.png")},
         {{rook,   white}, (":/MainWindow/Figures/Wr.png")},
         {{rook,   black}, (":/MainWindow/Figures/Br.png")},
         {{knight, white}, (":/MainWindow/Figures/Wn.png")},
         {{knight, black}, (":/MainWindow/Figures/Bn.png")},
         {{bishop, white}, (":/MainWindow/Figures/Wb.png")},
         {{bishop, black}, (":/MainWindow/Figures/Bb.png")}
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

    ~Figure() {

        qDebug() << "ia umer";
    }

private:


};







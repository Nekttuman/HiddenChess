#pragma once

#include <QtWidgets>
#include <qmap.h>
#include<qstring.h>
#include <tuple>


enum Ft {
    pawn,
    king,
    queen,
    rook,
    knight,
    bishop
};
enum Fc {
    white, black
};

typedef std::tuple<Ft, Fc> TwoKey;

const QMap<TwoKey, QString> FigureImages = {{{pawn,   white}, (":/HiddenChess/Figures/Wp.png")},
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
    Fc fColor;
    QString figureImage = "";
    bool fakeStatus;
    int x, y;

    Figure(Ft figure_, Fc fcolor_);

private:


};
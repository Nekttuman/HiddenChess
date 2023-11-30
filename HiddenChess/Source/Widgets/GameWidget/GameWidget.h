#pragma once

#include <QtWidgets>
#include "ui_GameWidget.h"
#include "SquareWidget.h"
#include "Figure.h"

class GameWidget : public QWidget {
Q_OBJECT


public:
    SquareWidget *squares[8][8];

public:
    GameWidget(QWidget *parent = nullptr);

    ~GameWidget();

private:
    Ui::GameWidgetClass ui;
    bool m_movesAllowed = false;

    void setField();

    void setFigures(Fc playerColor, Fc enemyColor);

    void setEnabledMoves(Figure *figure, int x, int y);

    void pawnAvailableMoves(Figure *figure, int x, int y);

    void kingAvailableMoves(Figure *figure, int x, int y);

    void queenAvailableMoves(Figure *figure, int x, int y);

    void rookAvailableMoves(Figure *figure, int x, int y);

    void knightAvailableMoves(Figure *figure, int x, int y);

    void bishopAvailableMoves(Figure *figure, int x, int y);

    void relocateKingWRook(int prevX, int prevY, int direction, Figure *king, QDropEvent *event);

signals:

    void backToMenu_signal();
    void move_signal(QPoint prevPoint, QPoint point);

private slots:

    void emitBackToMenu_slot() { emit backToMenu_signal(); }

public slots:

    void showMoves_slot(Figure *figure, int x, int y);

    void hideMoves_slot();

    void startGame_slot();

    void moveRequest_slot(int prevX, int prevY, int x, int y, QDropEvent *event);

protected:
    void paintEvent(QPaintEvent *event) override;

};



#pragma once

#include <QtWidgets>
#include "ui_GameWidget.h"
#include "SquareWidget.h"
#include "Figure.h"
#include "RoomSettings.h"


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
    RoomSettings m_rs;

    void setField();

    void setFigures(FigureColor playerColor, FigureColor enemyColor);

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

    void startAskingForMove_signal();

private slots:

    void emitBackToMenu_slot() { emit backToMenu_signal(); }

public slots:

    void showMoves_slot(Figure *figure, int x, int y);

    void opponentMadeMove_slot(QPoint prevPoint, QPoint point);

    void hideMoves_slot();

    void startGame_slot();

    void setSettings_slot(RoomSettings rs);

    void moveRequest_slot(int prevX, int prevY, int x, int y, QDropEvent *event);

    void allowMoves_slot();

protected:

    void resizeEvent(QResizeEvent *event) override;

};




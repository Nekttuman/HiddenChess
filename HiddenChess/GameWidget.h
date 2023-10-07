#pragma once

#include <QtWidgets>
#include "ui_GameWidget.h"
#include "Square.h"
#include "MyFunc.h"

class GameWidget : public QWidget {
Q_OBJECT


public:
    Square *squares[8][8];

public:
    GameWidget(QWidget *parent = nullptr);

    ~GameWidget();

private:
    Ui::GameWidgetClass ui;

    void setField();

    void setFigures(Fc playerColor, Fc enemyColor);

    void setEnabledMoves(Figure* figure, int x, int y);

    void pawnAvailableMoves(Figure* figure, int x, int y);
    void kingAvailableMoves(Figure* figure, int x, int y);
    void queenAvailableMoves(Figure* figure, int x, int y);
    void rookAvailableMoves(Figure* figure, int x, int y);
    void knightAvailableMoves(Figure* figure, int x, int y);
    void bishopAvailableMoves(Figure* figure, int x, int y);

    void relocateKingWRook(int prevX, int prevY, int direction, Figure* king, QDropEvent* event);

signals:

    void backToMenu_signal();

private slots:

    void emitBackToMenu_slot() { emit backToMenu_signal(); }


public slots:

    void showMoves_slot(Figure *figure, int x, int y);
    void hideMoves_slot();

    void startGame_slot();

    void setOpponentNick_slot(QString);
    void setHostNick_slot(QString nick){
        ui.hostNickLineEdit->setText(nick);
    }

    void moveRequest_slot(int prevX, int prevY, int x,int y, QDropEvent* event);

protected:
  void resizeEvent(QResizeEvent* event) override;

};




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

    void setFigures();

    TwoDimIntArray EnabledMoves(Ft figure, int x, int y);

signals:

    void backToMenu_signal();

private slots:

    void emitBackToMenu_slot() { emit backToMenu_signal(); }


public slots:

    void showMoves_slot(Figure *figure, int x, int y);
    void hideMoves_slot(Figure* figure, int x, int y);

    void startGame_slot();

    void setOpponentNick_slot(QString);
    void setHostNick_slot(QString nick){
        ui.hostNickLineEdit->setText(nick);
    }

};





#include "GameWidget.h"

GameWidget::GameWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);


    ui.gridLayout->setSpacing(0);


    connect(ui.startButton, &QPushButton::clicked, this, &GameWidget::startGame_slot);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            squares[i][j] = new Square(i, j, this);
            connect(squares[i][j], &Square::showMoves_signal, this, &GameWidget::showMoves_slot);
        }
    }

}

GameWidget::~GameWidget() {}


void GameWidget::setField() {

    qDebug() << "start";


    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {


            ui.gridLayout->addWidget(squares[i][k], i, k);
            squares[i][k]->show();

        }
    }

}


void GameWidget::startGame_slot() {

    setField();
    setFigures();

}

void GameWidget::setFigures() {

    for (int i = 0; i < 8; i++) {

        squares[1][i]->setFigureType(bishop, white);


    }
}


void GameWidget::showMoves_slot(Figure *figure, int x, int y) {

    qDebug() << x;
}
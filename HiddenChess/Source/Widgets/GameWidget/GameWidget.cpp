
#include "GameWidget.h"
#include <qsound.h>

GameWidget::GameWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);


    ui.gridLayout->setSpacing(0);
    ui.label_3->setText("ti dolbaaaeeeb");

    connect(ui.startButton, &QPushButton::clicked, this, &GameWidget::startGame_slot);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            squares[i][j] = new SquareWidget(i, j, this);
            connect(squares[i][j], &SquareWidget::showMoves_signal, this, &GameWidget::showMoves_slot);
            connect(squares[i][j], &SquareWidget::hideMoves_signal, this, &GameWidget::hideMoves_slot);
            connect(squares[i][j], &SquareWidget::moveRequest_signal, this, &GameWidget::moveRequest_slot);
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

void GameWidget::setFigures(Fc playerColor, Fc enemyColor) {

    for (int i = 0; i < 8; i++) {

        squares[6][i]->setFigureType(pawn, player, playerColor);
    }
    squares[7][0]->setFigureType(rook, player, playerColor);
    squares[7][7]->setFigureType(rook, player, playerColor);
    squares[7][1]->setFigureType(knight, player, playerColor);
    squares[7][6]->setFigureType(knight, player, playerColor);
    squares[7][4]->setFigureType(bishop, player, playerColor);
    squares[7][5]->setFigureType(bishop, player, playerColor);
    squares[7][3]->setFigureType(queen, player, playerColor);
    squares[7][2]->setFigureType(king, player, playerColor);


    for (int i = 0; i < 8; i++) {

        squares[1][i]->setFigureType(pawn, enemy, enemyColor);
    }
    squares[0][0]->setFigureType(rook, enemy, enemyColor);
    squares[0][7]->setFigureType(rook, enemy, enemyColor);
    squares[0][1]->setFigureType(knight, enemy, enemyColor);
    squares[0][6]->setFigureType(knight, enemy, enemyColor);
    squares[0][2]->setFigureType(bishop, enemy, enemyColor);
    squares[0][5]->setFigureType(bishop, enemy, enemyColor);
    squares[0][3]->setFigureType(queen, enemy, enemyColor);
    squares[0][4]->setFigureType(king, enemy, enemyColor);
}



//FiguresMoves######################################################################



void GameWidget::setEnabledMoves(Figure *figure, int x, int y) {
    figure->availableMoves.clear();
    switch (figure->figureType) {
        case pawn:
            pawnAvailableMoves(figure, x, y);
            break;

        case king:
            kingAvailableMoves(figure, x, y);
            break;

        case queen:
            queenAvailableMoves(figure, x, y);
            break;


        case rook:
            rookAvailableMoves(figure, x, y);
            break;

        case knight:
            knightAvailableMoves(figure, x, y);
            break;

        case bishop:
            bishopAvailableMoves(figure, x, y);
            break;


        default:
            break;
    }
}


void GameWidget::pawnAvailableMoves(Figure *figure, int x, int y) {
    if (x > 0) {
        try {
            if (squares[x - 1][y - 1]->Ffigure != nullptr) {
                if (squares[x - 1][y - 1]->Ffigure->playerType == enemy) figure->availableMoves.append({x - 1, y - 1});
            }
        }
        catch (...) {}
        try {
            if (squares[x - 1][y + 1]->Ffigure != nullptr) {
                if (squares[x - 1][y + 1]->Ffigure->playerType == enemy) figure->availableMoves.append({x - 1, y + 1});
            }
        }
        catch (...) {}

    }

    if (x > 0)
        if (squares[x - 1][y]->Ffigure == nullptr) {

            figure->availableMoves.append({x - 1, y});
        } else return;

    if (x > 5 && squares[x - 2][y]->Ffigure == nullptr)
        figure->availableMoves.append({x - 2, y}); //два шага (первый ход)

}


void GameWidget::kingAvailableMoves(Figure *figure, int x, int y) {

    if (figure->FirstMoveDone == false) {
        int i = y;
        while (i < 7) {
            if (squares[x][++i]->Ffigure != nullptr) {
                if (squares[x][i]->Ffigure->figureType != rook && squares[x][i]->Ffigure->playerType != player) break;
                if (squares[x][i]->Ffigure->FirstMoveDone == false) {
                    if (i - y < 3) figure->availableMoves.append({x, y + 1});
                    else figure->availableMoves.append({x, y + 2});

                } else break;
            }
        }

        i = y;
        while (i > 0) {
            if (squares[x][--i]->Ffigure != nullptr) {
                if (squares[x][i]->Ffigure->figureType != rook && squares[x][i]->Ffigure->playerType != player) break;
                if (squares[x][i]->Ffigure->FirstMoveDone == false) {
                    if (y - i < 3) figure->availableMoves.append({x, y - 1});
                    else figure->availableMoves.append({x, y - 2});

                } else break;
            }
        }
    }

    for (int i = -1; i < 2; ++i) {
        for (int k = -1; k < 2; ++k) {
            if (!((x - i < 0 || x - i > 7) || (y - k < 0 || y - k > 7) || (i == 0 && k == 0)))
                if (squares[x - i][y - k]->Ffigure == nullptr) figure->availableMoves.append({x - i, y - k});
                else if (squares[x - i][y - k]->Ffigure->playerType == enemy)
                    figure->availableMoves.append({x - i, y - k});
        }
    }
}


void GameWidget::queenAvailableMoves(Figure *figure, int x, int y) {
    for (int i = -1; i < 2; i += 2) {
        for (int j = 0; j < 8; ++j) {
            int newX = x;
            int newY = y;

            while (true) {
                newX += i;
                if (newX < 0 || newX >= 8) break;

                // Проверяем, есть ли фигура на пути, и если есть, прерываем цикл
                if (squares[newX][y]->Ffigure != nullptr) {
                    if (squares[newX][y]->Ffigure->playerType == enemy) {
                        figure->availableMoves.append({newX, y});
                        break;
                    } else break;
                }

                figure->availableMoves.append({newX, y});
            }

            while (true) {
                newY += i;
                if (newY < 0 || newY >= 8) break;

                // Проверяем, есть ли фигура на пути, и если есть, прерываем цикл
                if (squares[x][newY]->Ffigure != nullptr) {
                    if (squares[x][newY]->Ffigure->playerType == enemy) {
                        figure->availableMoves.append({x, newY});
                        break;
                    } else break;
                }

                figure->availableMoves.append({x, newY});
            }
        }
    }

    // Движение как слон (по диагонали)
    for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
            for (int k = 1; k < 8; ++k) {
                int newX = x + k * i;
                int newY = y + k * j;
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                    if (squares[newX][newY]->Ffigure == nullptr) {
                        figure->availableMoves.append({newX, newY});
                    } else {
                        if (squares[newX][newY]->Ffigure->playerType == enemy) {
                            figure->availableMoves.append({newX, newY});
                            break;
                        } else break;
                    }
                } else {
                    break; // Прерываем, если выходим за пределы доски
                }
            }
        }
    }
}


void GameWidget::rookAvailableMoves(Figure *figure, int x, int y) {
    for (int i = -1; i < 2; i += 2) {
        for (int j = 0; j < 8; ++j) {
            int newX = x;
            int newY = y;

            while (true) {
                newX += i;
                if (newX >= 0 && newX < 8) {
                    if (squares[newX][y]->Ffigure == nullptr) figure->availableMoves.append({newX, y});
                    else {
                        if (squares[newX][y]->Ffigure->playerType == enemy) {
                            figure->availableMoves.append({newX, y});
                            break;
                        } else break;
                    }
                } else break;
            }

            while (true) {
                newY += i;
                if (newY >= 0 && newY < 8) {
                    if (squares[x][newY]->Ffigure == nullptr) figure->availableMoves.append({x, newY});
                    else {
                        if (squares[x][newY]->Ffigure->playerType == enemy) {
                            figure->availableMoves.append({x, newY});
                            break;
                        } else break;
                    }
                } else break;
            }
        }
    }
}


void GameWidget::knightAvailableMoves(Figure *figure, int x, int y) {
    for (int i = 0; i < 8; ++i) {
        int newX = x + knightMoves[i][0];
        int newY = y + knightMoves[i][1];

        // Проверка, что новые координаты находятся на доске (8x8)
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            if (squares[newX][newY]->Ffigure == nullptr) {
                figure->availableMoves.append({newX, newY});
            } else if (squares[newX][newY]->Ffigure->playerType == enemy) {
                figure->availableMoves.append({newX, newY});
            }
        }
    }

}


void GameWidget::bishopAvailableMoves(Figure *figure, int x, int y) {
    for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
            for (int k = 1; k < 8; ++k) {
                int newX = x + k * i;
                int newY = y + k * j;
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                    if (squares[newX][newY]->Ffigure == nullptr) {
                        figure->availableMoves.append({newX, newY});
                    } else {
                        if (squares[newX][newY]->Ffigure->playerType == enemy) {
                            figure->availableMoves.append({newX, newY});
                            break;
                        } else break;
                    }
                } else {
                    break; // Прерываем, если выходим за пределы доски
                }
            }
        }
    }
}


//End Figures Moves########################################################################

//Slots####################################################################################

void GameWidget::showMoves_slot(Figure *figure, int x, int y) {

    setEnabledMoves(figure, x, y);
    for (auto coordinate: figure->availableMoves) {

        squares[coordinate.x()][coordinate.y()]->lightSquare();

    }
}


void GameWidget::hideMoves_slot() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            squares[i][j]->hideSquare();
        }
    }
}


void GameWidget::relocateKingWRook(int prevX, int prevY, int direction, Figure *king, QDropEvent *event) {

    int i = prevY;
    while (i >= 0 && i < 8 && squares[prevX][i += direction]->Ffigure == nullptr) {}

    Figure *buffer = squares[prevX][i]->Ffigure;

    if (buffer->figureType == rook) {
        squares[prevX][i]->removeFigure();

        if (abs(prevY - i) < 3) {
            squares[prevX][prevY]->placeFigure(buffer);
            squares[prevX][prevY + direction]->placeFigure(king);
        } else {
            squares[prevX][prevY + direction]->placeFigure(buffer);
            squares[prevX][prevY + direction * 2]->placeFigure(king);
            squares[prevX][prevY]->removeFigure();
        }
        buffer->FirstMoveDone = true;
        king->FirstMoveDone = true;

        return;
    }

    event->setDropAction(Qt::IgnoreAction);
}


void GameWidget::startGame_slot() {

    setField();
    setFigures(black, white);
    m_movesAllowed = true;

}


void GameWidget::moveRequest_slot(int prevX, int prevY, int x, int y, QDropEvent *event) {

    Figure *prevFigure = squares[prevX][prevY]->Ffigure;
    if (!m_movesAllowed) {
        qDebug() << "Moves not allowed";
        return;
    }

    if (prevFigure->figureType == king && prevFigure->FirstMoveDone == false &&
        (abs(y - prevY == 2) || (squares[x][y]->Ffigure != nullptr &&
                                 squares[x][y]->Ffigure->figureType == rook))) {

        relocateKingWRook(prevX, prevY, y > prevY ? 1 : -1, prevFigure, event);

    } else if ((x != prevX || y != prevY) && squares[x][y]->Ffigure == nullptr) {

        squares[x][y]->placeFigure(prevFigure);
        squares[prevX][prevY]->removeFigure();

    } else if (squares[x][y]->Ffigure->playerType == enemy) {

        squares[x][y]->placeFigure(prevFigure);
        squares[prevX][prevY]->removeFigure();

    } else {

        event->setDropAction(Qt::IgnoreAction);
        return;
    }

    emit move_signal(QPoint(prevX, prevY), QPoint(x,y));

    if (prevFigure->fakeStatus == false && !prevFigure->availableMoves.contains(QPoint(x, y))) {
        prevFigure->fakeStatus = true;
        qDebug() << "fake";
    }

}


//End Slots################################################################################

void GameWidget::paintEvent(QPaintEvent *event) {

    QRect widgetSize = ui.gridLayout->geometry();
    int width = widgetSize.width();
    int height = widgetSize.height();
    int minSize = (width < height) ? width : height;

    ui.gridLayout->setGeometry(QRect(widgetSize.topLeft(), QSize(minSize, minSize)));

    QWidget::paintEvent(event);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            squares[i][j]->resizePicture();
        }
    }
}


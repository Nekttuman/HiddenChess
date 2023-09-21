
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
            connect(squares[i][j], &Square::hideMoves_signal, this, &GameWidget::hideMoves_slot);
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

void GameWidget::setFigures() {

    for (int i = 0; i < 8; i++) {

        squares[6][i]->setFigureType(pawn, white);
    }
    squares[7][0]->setFigureType(rook, white);
    squares[7][7]->setFigureType(rook, white);
    squares[7][1]->setFigureType(knight, white);
    squares[7][6]->setFigureType(knight, white);
    squares[7][2]->setFigureType(bishop, white);
    squares[7][5]->setFigureType(bishop, white);
    squares[7][3]->setFigureType(queen, white);
    squares[7][4]->setFigureType(king, white);
}


void GameWidget::startGame_slot() {

    setField();
    setFigures();

}



TwoDimIntArray GameWidget::EnabledMoves(Ft figure, int x, int y) {

  TwoDimIntArray list;

  switch (figure) {
  case pawn:

    if (x > 0)  list.append({ x - 1, y }); // Один шаг вперед
    if (x == 6) list.append({ x - 2, y }); //два шага (первый ход)
    break;
  case king:
    for (int i = -1; i < 2; ++i) {
      for (int k = -1; k < 2; ++k) {
        if(!((x-i<0 || x-i>7) || (y - k < 0 || y - k>7) || (i==0 && k==0))) list.append({ x - i, y-k });
      }
    }
    break;
  case queen:
    // Движение как ладья (вертикально и горизонтально)
    for (int i = -1; i < 2; i += 2) {
      for (int j = 0; j < 8; ++j) {
        int newX = x;
        int newY = y;

        while (true) {
          newX += i;
          if (newX < 0 || newX >= 8) break;
          list.append({ newX, y });
        }

        while (true) {
          newY += i;
          if (newY < 0 || newY >= 8) break;
          list.append({ x, newY });
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
            list.append({ newX, newY });
          }
          else {
            break; // Прерываем, если выходим за пределы доски
          }
        }
      }
    }
    break;
  
  case rook:
    // Движение как ладья (вертикально и горизонтально)
    for (int i = -1; i < 2; i += 2) {
      for (int j = 0; j < 8; ++j) {
        int newX = x;
        int newY = y;

        while (true) {
          newX += i;
          if (newX < 0 || newX >= 8) break;
          list.append({ newX, y });
        }

        while (true) {
          newY += i;
          if (newY < 0 || newY >= 8) break;
          list.append({ x, newY });
        }
      }
    }
    break;

  case knight:
    // Все возможные ходы коня
    

    for (int i = 0; i < 8; ++i) {
      int newX = x + knightMoves[i][0];
      int newY = y + knightMoves[i][1];

      // Проверка, что новые координаты находятся на доске (8x8)
      if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
        list.append({ newX, newY });
      }
    }
    break;

  case bishop:
    // Движение как слон (по диагонали)
    for (int i = -1; i < 2; i += 2) {
      for (int j = -1; j < 2; j += 2) {
        for (int k = 1; k < 8; ++k) {
          int newX = x + k * i;
          int newY = y + k * j;
          if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            list.append({ newX, newY });
          }
          else {
            break; // Прерываем, если выходим за пределы доски
          }
        }
      }
    }
    break;


  default:
    break;
  }

  

  return list;
}



void GameWidget::showMoves_slot(Figure* figure, int x, int y) {

  TwoDimIntArray list = EnabledMoves(figure->figureType, x, y);
  if (!list.isEmpty()){
    foreach(const QList<int>&coordinates, list) {

      squares[coordinates.at(0)][coordinates.at(1)]->lightSquare();


    }
  
  }
  
}

void GameWidget::hideMoves_slot(Figure* figure, int x, int y) {

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
    
      squares[i][j]->hideSquare();
    
    }
  }

}
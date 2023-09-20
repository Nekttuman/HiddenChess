
#include "GameWidget.h"

GameWidget::GameWidget(QWidget* parent)
  : QWidget(parent)
{
  ui.setupUi(this);
  

  ui.gridLayout->setSpacing(0);
  connect(ui.startButton, &QPushButton::clicked, this, &GameWidget::startGame_slot);
}

GameWidget::~GameWidget()
{}


void GameWidget::setField() {

  qDebug() << "start";

 

  for (int i = 0; i < 8; i++) {
    for (int k = 0; k < 8; k++) {

      squares[i][k] = new Square(i, k, this);

      ui.gridLayout->addWidget(squares[i][k], i, k);
      squares[i][k]->show();

    }
  }
  
}
//
//void GameWidget::paintEvent(QPaintEvent* event) {
//    // resize pics when squares resized
//  if (squares[0][0]!=nullptr)
//    imageManager.pawnImg = imageManager.pawnImg.scaled(squares[0][0]->size(), Qt::KeepAspectRatio);
//
//
//}




void GameWidget::startGame_slot() {

  setField();
  setFigures();

}

void GameWidget::setFigures() {

  for (int i = 0; i < 8; i++) {

    squares[1][i]->setFigureType(bishop, white);


  }
}
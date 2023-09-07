
#include "GameWidget.h"

GameWidget::GameWidget(QWidget* parent)
  : QWidget(parent)
{
  ui.setupUi(this);
  

  ui.gridLayout->setSpacing(0);
  connect(ui.startButton, &QPushButton::clicked, this, &GameWidget::startGame);
}

GameWidget::~GameWidget()
{}


void GameWidget::setGame() {

  qDebug() << "start";

 

  for (int i = 0; i < 8; i++) {
    for (int k = 0; k < 8; k++) {

      squares[i][k] = new Square(i, k, this);

      ui.gridLayout->addWidget(squares[i][k], i, k);
      squares[i][k]->show();

    }
  }
  
}


void GameWidget::setFigures() {

  ImgManager pawn = ImgManager();
  for (int i = 0; i < 8; i++) {

    squares[1][i]->setFigureType(FigureType::pawn, pawn.pawnImg);


  }

}




void GameWidget::startGame() {

  setGame();
  setFigures();

}




//void GameWidget::paintEvent(QPaintEvent* event) {
//  if (squares[0][0] != nullptr) {
//    imageManager.pawnImg = imageManager.pawnImg.scaled(squares[0][0]->size(), Qt::KeepAspectRatio);
//    
//  
//  
//  }
//
//}

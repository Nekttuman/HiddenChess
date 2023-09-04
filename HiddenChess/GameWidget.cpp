
#include "GameWidget.h"

GameWidget::GameWidget(QWidget* parent)
  : QWidget(parent)
{
  ui.setupUi(this);
  /*Square* image = new Square();
  ui.gridLayout->addWidget(image);*/
  //SetGame();

  connect(ui.startButton, &QPushButton::clicked, this, &GameWidget::setGame);
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

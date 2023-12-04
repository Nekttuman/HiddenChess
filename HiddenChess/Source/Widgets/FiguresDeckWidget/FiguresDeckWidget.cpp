//
// Created by 79140 on 12/4/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FiguresDeckWidget.h" resolved

#include "FiguresDeckWidget.h"
#include "ui_FiguresDeckWidget.h"


FiguresDeckWidget::FiguresDeckWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::FiguresDeckWidget) {
    ui->setupUi(this);
}

FiguresDeckWidget::~FiguresDeckWidget() {
    delete ui;
}

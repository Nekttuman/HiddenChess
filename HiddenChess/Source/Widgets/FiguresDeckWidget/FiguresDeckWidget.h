//
// Created by 79140 on 12/4/2023.
//

#ifndef HIDDENCHESS_FIGURESDECKWIDGET_H
#define HIDDENCHESS_FIGURESDECKWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class FiguresDeckWidget; }
QT_END_NAMESPACE

class FiguresDeckWidget : public QWidget {
Q_OBJECT

public:
    explicit FiguresDeckWidget(QWidget *parent = nullptr);

    ~FiguresDeckWidget() override;

private:
    Ui::FiguresDeckWidget *ui;
};


#endif //HIDDENCHESS_FIGURESDECKWIDGET_H

#include "MainWindow.h"
#include "GameWidget.h"
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
//    GameWidget w;
//    w.show();
    MainWindow hc(nullptr);
    hc.show();



    return app.exec();
}
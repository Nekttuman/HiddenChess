#include "HiddenChess.h"
#include "GameWidget.h"
#include <QMainWindow>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameWidget w;
    w.show();


    return app.exec();
}
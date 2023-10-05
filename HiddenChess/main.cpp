#include "HiddenChess.h"
#include "GameWidget.h"
#include <QMainWindow>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
//    GameWidget w;
//    w.show();
HiddenChess hc;
hc.show();

    return app.exec();
}
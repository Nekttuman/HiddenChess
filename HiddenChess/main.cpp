#include "HiddenChess.h"
#include <QtWidgets/QApplication>
//#include "GameWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HiddenChess w;
    w.show();

//GameWidget gw;
//gw.show();

    return a.exec();
}

#include "HiddenChess.h"
#include "ChatWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HiddenChess w;
    w.show();

    return a.exec();
}

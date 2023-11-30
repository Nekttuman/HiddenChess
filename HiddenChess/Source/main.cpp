#include "MainWindow.h"
#include "GameWidget.h"
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);



//    GameWidget gw;
//    gw.show();


// Load an application style
    QFile styleFile(":/MainWindow/style.qss");
    styleFile.open(QFile::ReadOnly);
    qDebug() << "Style file opened: " << styleFile.isOpen();

// Apply the loaded stylesheet
    QString style(styleFile.readAll());


    MainWindow mw(nullptr);
    mw.show();

    app.setStyleSheet(style);
    app.style()->unpolish(&mw);
    app.style()->polish(&mw);

    return app.exec();
}
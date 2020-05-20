#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setGeometry(50,0,750,500);
    w.setWindowIcon(QIcon(":/flambagestypes.gif"));
    w.setWindowTitle("OMYXAir - Mode de Fonctionnement : OFF");
    return a.exec();
}

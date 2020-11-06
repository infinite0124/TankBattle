#include "mainwindow.h"
#include "subwindow.h"
#include <QApplication>
#include "tankwar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

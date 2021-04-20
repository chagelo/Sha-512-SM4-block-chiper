#include "mainwindow.h"
#include <QApplication>
#include "SM4.h"
#include <cstring>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include "config/config_sqlconnect.h"
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    config_sqlconnect KN;
    KN.connectsql();
    MainWindow w;
    w.show();

    return a.exec();
}

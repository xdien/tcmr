#include "mainwindow.h"
#include <QApplication>
#include "config/config_sqlconnect.h"
#include <QtPlugin>
#ifdef __MINGW32__
    #if defined __MINGW64_VERSION_MAJOR && defined __MINGW64_VERSION_MINOR
        Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
    #else
        // mingw

    #endif
#else
    // other toolchain
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    config_sqlconnect KN;
    KN.connectsql();
    MainWindow w;
    w.show();

    return a.exec();
}

#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T20:15:57
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = module
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_setting.cpp \
    config/config_sqlconnect.cpp \
    dangkyphieutiem.cpp \
    login.cpp \
    khamsobo.cpp \
    managerstt.cpp \
    manageindex.cpp \
    dongphi.cpp \
    tiemngua.cpp \
    danhsachboqua.cpp \
    dialog_jumstt.cpp \
    testwg.cpp

HEADERS  += mainwindow.h \
    dialog_setting.h \
    config/config_sqlconnect.h \
    dangkyphieutiem.h \
    login.h \
    khamsobo.h \
    managerstt.h \
    manageindex.h \
    dongphi.h \
    tiemngua.h \
    danhsachboqua.h \
    dialog_jumstt.h \
    testwg.h

FORMS    += mainwindow.ui \
    dialog_setting.ui \
    dangkyphieutiem.ui \
    login.ui \
    khamsobo.ui \
    dongphi.ui \
    tiemngua.ui \
    danhsachboqua.ui \
    testwg.ui

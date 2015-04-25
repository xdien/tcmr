#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T20:15:57
#
#-------------------------------------------------

QT       += core gui sql xml webkitwidgets  printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = module
TEMPLATE = app
#include(../QtRPT/QtRPT.pri)
linux{
INCLUDEPATH += /home/xdien/QtSDK/NCReport/include
LIBS += -L/home/xdien/QtSDK/NCReport/lib -lNCReport
copydata.commands = $(COPY_DIR) $$PWD/report $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
}


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
    tracuuphieuhen.cpp \
    managenv.cpp \
    managetiemngua.cpp \
    managechucvu.cpp \
    nhapthuoc.cpp \
    reporttctre.cpp \
    managerlogin.cpp \
    htmltemp.cpp \
    reportbenhtruyennhiem.cpp \
    qlbenhthuoc.cpp \
    managebenhvathuoc.cpp \
    managegia.cpp

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
    tracuuphieuhen.h \
    managenv.h \
    managetiemngua.h \
    managechucvu.h \
    nhapthuoc.h \
    reporttctre.h \
    managerlogin.h \
    htmltemp.h \
    reportbenhtruyennhiem.h \
    managebenhvathuoc.h \
    managegia.h

FORMS    += mainwindow.ui \
    dialog_setting.ui \
    dangkyphieutiem.ui \
    login.ui \
    khamsobo.ui \
    dongphi.ui \
    tiemngua.ui \
    danhsachboqua.ui \
    tracuuphieuhen.ui \
    managenv.ui \
    managetiemngua.ui \
    managechucvu.ui \
    nhapthuoc.ui \
    reporttctre.ui \
    reportbenhtruyennhiem.ui \
    managebenhvathuoc.ui \
    managegia.ui

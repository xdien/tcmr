#include "managerstt.h"

#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QDate>

managerSTT::managerSTT()
{
    QSettings sett("stt.ini",QSettings::IniFormat);
    idx = 0;
    arridx = 0;
    sett.beginGroup("STT");
//    sett.beginReadArray("ignore");
//    sett.setArrayIndex(0);
//    sett.setValue("tt","sadasd");
    tmpidx = sett.value("index").toInt();
    date = sett.value("date").toString();
    if(tmpidx <= 0|| date != QDate::currentDate().toString("dd/MM/yyyy")){
        sett.setValue("index", QString::number(idx));
        date = QDate::currentDate().toString("dd/MM/yyyy");
        sett.setValue("date",date);
    }else{
        idx = sett.value("index").toInt();
    }
}

managerSTT::~managerSTT()
{
}
int managerSTT::getcurrentindex()
{
    return idx;
}
int managerSTT::next()
{
    QSettings sett("stt.ini",QSettings::IniFormat);
    sett.beginGroup("STT");
    idx = sett.value("index").toInt();
    idx = idx +1;
    sett.setValue("index", QString::number(idx));
    return idx;
}
void managerSTT::setIDX(int stt)
{
    QSettings sett("stt.ini",QSettings::IniFormat);
    sett.beginGroup("STT");
    idx = stt;
    sett.setValue("index", QString::number(stt));
}

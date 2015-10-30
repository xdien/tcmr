#include "managerstt.h"

#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QDate>

managerSTT::managerSTT(QString beginGroup_name)
{
    QSettings sett("stt.ini",QSettings::IniFormat);
    idx = 0;
    arridx = 0;
    group_name = beginGroup_name;
    sett.beginGroup(group_name);
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
void managerSTT::setbeginGroupName(QString name){
    group_name = name;
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
    sett.beginGroup(group_name);
    idx = sett.value("index").toInt();
    idx = idx +1;
    sett.setValue("index", QString::number(idx));
    return idx;
}
void managerSTT::setIDX(int stt)
{
    QSettings sett("stt.ini",QSettings::IniFormat);
    sett.beginGroup(group_name);
    idx = stt;
    sett.setValue("index", QString::number(stt));
}

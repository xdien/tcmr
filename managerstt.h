#ifndef MANAGERSTT_H
#define MANAGERSTT_H
#include <QXmlStreamWriter>
#include <QDomElement>
#include <QDomDocument>
#include <QDomNodeList>
#include <QFile>
#include <QtSql>
#include <QDate>

class managerSTT
{
public:
    int STT;
    managerSTT(QString beginGroup_name);
    int getcurrentindex();
    int next();
    ~managerSTT();
    void setIDX(int stt);
    void setbeginGroupName(QString name);
private:
    QDomElement root;
    QDomDocument doc;
    QDomElement nodeTag;
    QDomNodeList elems;
    QFile xmlFile;
    int arridx, idx, tmpidx;
    QString date;
    QString group_name;
};

#endif // MANAGERSTT_H

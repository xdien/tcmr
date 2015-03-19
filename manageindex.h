#ifndef MANAGEINDEX_H
#define MANAGEINDEX_H
#include <QtSql>
#include <QDebug>

class manageIndex
{
public:
    manageIndex();
    ~manageIndex();
private:
    QSqlQuery query;
    QString table_name, index_code;
    int idx;
    //QString prefix;
public:
    void setPrefix(QString Prefix);
    QString getNextIndexCode(QString tableName, QString prefix);
};

#endif // MANAGEINDEX_H

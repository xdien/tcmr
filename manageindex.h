#ifndef MANAGEINDEX_H
#define MANAGEINDEX_H
#include <QtSql>
#include <QDebug>
 #include <QVarLengthArray>

class manageIndex
{
public:
    manageIndex();
    ~manageIndex();
private:
    QSqlQuery query;
    QString table_name, index_code,num_prefix,str_num;
    QVarLengthArray<QString, 10> array;
    qint32 idx;
    //QString prefix;
public:
    void setPrefix(QString Prefix);
    QString getNextIndexCode(QString tableName, QString prefix);
};

#endif // MANAGEINDEX_H

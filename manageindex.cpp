#include "manageindex.h"

manageIndex::manageIndex()
{

}

manageIndex::~manageIndex()
{

}

QString manageIndex::getNextIndexCode(QString tableName, QString prefix)
{
    query.exec("select * from "+tableName+" order by 1 desc limit 1");
    if(query.next())
    {
        //lay ma ra, tach so , tang so len 1 va gop so do voi prefix
        index_code = query.value(0).toString();
        idx = index_code.mid(3).toInt();
        idx = idx +1;
        index_code = prefix +"_"+QString::number(idx);
    }else{
        qDebug() << "Can't get value form table name, default value is use";
        qDebug() << query.lastError().text();
        index_code = prefix+"_0";
    }
    return index_code;
}

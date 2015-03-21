#include "manageindex.h"

manageIndex::manageIndex()
{
    num_prefix = "00000000";
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
        idx = index_code.mid(3).toDouble();
        idx = idx +1;
        str_num = QString::number(idx);//doi thanh string lay so ky tu
        index_code = prefix +"_"+num_prefix.mid(str_num.length())+str_num;
    }else{
        str_num = "0";
        qDebug() << "Can't get value form table name, default value is use";
        qDebug() << query.lastError().text();
        index_code = prefix +"_"+num_prefix.mid(str_num.length())+str_num;
    }
    return index_code;
}

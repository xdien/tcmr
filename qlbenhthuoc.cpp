#include "qlbenhthuoc.h"

qlbenhthuoc::qlbenhthuoc()
{

}

qlbenhthuoc::~qlbenhthuoc()
{

}

void qlbenhthuoc::setQuery(QString query)
{
    str = query;

    qDebug() << "goi nek" << selectStatement()<< this->filter()<< query;
}
QString qlbenhthuoc::selectStatement() const
{
    return "SELECT distinct don_gia.ma_dm,gia "
            "FROM don_gia right join (select ma_dm,max(ma_dongia) as ma_dg, max(ngay) from don_gia group by ma_dm) as aa on aa.ma_dg = don_gia.ma_dongia";
}

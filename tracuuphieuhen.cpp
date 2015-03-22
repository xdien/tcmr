#include "tracuuphieuhen.h"
#include "ui_tracuuphieuhen.h"

tracuuPhieuHen::tracuuPhieuHen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tracuuPhieuHen)
{
    ui->setupUi(this);
    ui->benhdk->setModel(&itemtDSbenh);
    ui->thuoc->setModel(&thuocModel);
}

tracuuPhieuHen::~tracuuPhieuHen()
{
    delete ui;
}

void tracuuPhieuHen::on_pushButton_2_clicked()
{

    //hien thi thong tin benh dk
    query.exec("select ten_benh, benh.ma_benh from tt_benh_nhan \
                right join muon_tiem on muon_tiem.ma_bn = tt_benh_nhan.ma_bn \
                left join benh on benh.ma_benh = muon_tiem.ma_benh where muon_tiem.ma_bn = '"+ ui->lineEdit->text() +"'" );
   while(query.next())
    {
            this->itemtDSbenh.appendRow(this->prepareRow(query.value(0).toString(),query.value(1).toString(),""));
}

            qDebug() << query.lastError().text();
            thuocModel.setQuery("select thuoc.ten_thuoc,count(thuoc.ma_thuoc) from tiem left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc \
                                where thuoc.ma_thuoc = '"+ui->lineEdit_mathuoc->text() +"' and ma_bn = '"+ui->lineEdit->text()+"' group by thuoc.ten_thuoc");
    qDebug() << thuocModel.lastError().text();
}

QList<QStandardItem *> tracuuPhieuHen::prepareRow(const QString &first,
                                                const QString &second,
                                                const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}

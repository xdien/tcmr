#include "tracuuphieuhen.h"
#include "ui_tracuuphieuhen.h"

tracuuPhieuHen::tracuuPhieuHen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tracuuPhieuHen)
{
    ui->setupUi(this);
    ui->benhdk->setModel(&itemtDSbenh);
    ui->thuoc->setModel(&thuocModel);
    stt = new managerSTT("dangkytt");
}

tracuuPhieuHen::~tracuuPhieuHen()
{
    delete ui;
}

void tracuuPhieuHen::on_pushButton_2_clicked()
{
    ui->kq->setText("");
    //hien thi thong tin benh dk
    //hien thi danh sach benh dang ky
    query.exec("select ten_benh, benh.ma_benh from tt_benh_nhan \
               right join muon_tiem on muon_tiem.ma_bn = tt_benh_nhan.ma_bn \
            left join benh on benh.ma_benh = muon_tiem.ma_benh where muon_tiem.ma_bn = '"+ ui->ma_bn->text() +"'" );
            while(query.next())
            {
                    this->itemtDSbenh.appendRow(this->prepareRow(query.value(0).toString(),query.value(1).toString(),""));
        }
                    query.exec("select thuoc.ten_thuoc,count(thuoc.ma_thuoc),thuoc.ma_thuoc from tiem left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc \
                               where tiem.ngay_tiem is not null and thuoc.ma_thuoc = '"+ui->lineEdit_mathuoc->text() +"' and ma_bn = '"+ui->ma_bn->text()+"' group by thuoc.ma_thuoc");
                    if(query.next())
            {
                    thuocModel.appendRow(this->prepareRow(query.value(0).toString(),query.value(1).toString(),query.value(2).toString()));
        }else{
                    ui->kq->setText("Khong tim thay");
        }
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

void tracuuPhieuHen::on_pushButton_clicked()
{
    //lap phieu tiem
    ma_bn =ui->ma_bn->text();
    for (int i =0; i < thuocModel.rowCount();i++) {
        query.exec("select stt_lieu from tiem where ma_bn = '"+ma_bn+"' and ma_thuoc ='"+thuocModel.index(i,2).data().toString()+"' order by 1 desc ");
        if(query.next())
        {
            mui_tiem = query.value(0).toInt();
            mui_tiem = mui_tiem +1;
            query.exec("update tiem set tai_hen_lan = '"+QString::number(mui_tiem)+"',ngay_dk_tai_hen = current_date where ma_bn = '"+ma_bn+"' and ma_thuoc ='"+thuocModel.index(i,2).data().toString()+"'");
        }else{
            qDebug() << query.lastError();
        }
    }
    //lam moi tt benh nhan de lap phieu
    stt_benh = stt->getcurrentindex();
    query.exec("update tt_benh_nhan set ngay_lap = current_date,lap_phieu = NULL,tai_hen =TRUE, stt = '"+QString::number(stt_benh)+"' where ma_bn ='"+ma_bn+"'");
    stt->next();
}

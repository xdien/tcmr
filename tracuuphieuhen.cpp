#include "tracuuphieuhen.h"
#include "ui_tracuuphieuhen.h"

tracuuPhieuHen::tracuuPhieuHen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tracuuPhieuHen)
{
    ui->setupUi(this);
    danhsachgoiYBenh.setQuery("select ten_benh,ma_benh from benh where la_vx = TRUE ");
    ui->dsbenh->setModel(&danhsachgoiYBenh);
    ui->benhdk->setModel(&itemtDSbenh);
    ui->thuoc->setModel(&thuocModel);
    stt = new managerSTT("dangkytt");
}

tracuuPhieuHen::~tracuuPhieuHen()
{
    delete ui;
    delete stt;
}

void tracuuPhieuHen::on_pushButton_2_clicked()
{
    this->itemtDSbenh.clear();
    //this->thuocModel.clear();
    ui->kq->setText("");
    //hien thi thong tin benh dk
    //hien thi danh sach benh dang ky
    query.exec("select ten_benh, benh.ma_benh,muon_tiem.ma_bn from tt_benh_nhan "
               "right join muon_tiem on muon_tiem.ma_bn = tt_benh_nhan.ma_bn "
               "left join benh on benh.ma_benh = muon_tiem.ma_benh where muon_tiem.ma_bn ilike '%"+ ui->ma_bn->text() +"'" );
    while(query.next())
    {
        ui->ma_bn->setText(query.value(2).toString());
        tmp = itemtDSbenh.findItems(query.value(1).toString(),Qt::MatchExactly, 1);
        if(tmp.count() <= 0)
        {
            this->itemtDSbenh.appendRow(this->prepareRow(query.value(0).toString(),query.value(1).toString(),""));
        }
    }

    query.exec("select thuoc.ten_thuoc,count(thuoc.ma_thuoc),thuoc.ma_thuoc from tiem left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc \
     where tiem.ngay_tiem is not null and thuoc.ma_thuoc ilike '%"+ui->lineEdit_mathuoc->text() +"' and ma_bn = '"+ui->ma_bn->text()+"' group by thuoc.ma_thuoc");
    qDebug() << query.lastQuery();
    if(query.next())
    {
        tmp = thuocModel.findItems(query.value(2).toString(),Qt::MatchExactly,2);
        if(tmp.count() <= 0)
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
    //cap nhat benh moi
    for(int i = 0; i <  dsbenhmoi.count(); i++){
    query.exec("INSERT INTO muon_tiem(\
               ma_benh, ma_bn, moi_dk)\
       VALUES ('"+ dsbenhmoi.at(i) +"', '"+ma_bn+"', TRUE);");
    }

    //lam moi tt benh nhan de lap phieu
    stt_benh = stt->getcurrentindex();
    query.exec("update tt_benh_nhan set ngay_lap = current_date,lap_phieu = NULL,tai_hen =TRUE, stt = '"+QString::number(stt_benh)+"' where ma_bn ='"+ma_bn+"'");
    stt->next();
    query.exec("NOTIFY khamsobo");
    this->itemtDSbenh.clear();
    this->thuocModel.clear();
}

void tracuuPhieuHen::on_dsbenh_clicked(const QModelIndex &index)
{
    ma_benh =danhsachgoiYBenh.index(index.row(),1).data().toString();
    tmp = itemtDSbenh.findItems(ma_benh,Qt::MatchExactly,1);
    if(tmp.count() <= 0)
    {
        dsbenhmoi.append(ma_benh);
        itemtDSbenh.appendRow(this->prepareRow(danhsachgoiYBenh.index(index.row(),0).data().toString(),ma_benh,""));
    }
}

void tracuuPhieuHen::on_pushButton_3_clicked()
{
    ma_benh = itemtDSbenh.index(ui->benhdk->currentIndex().row(),1).data().toString();
    itemtDSbenh.removeRow(ui->benhdk->currentIndex().row());
    for(int i; i < dsbenhmoi.count();i++)
    {
        if(dsbenhmoi.at(i) == ma_benh)
        {
            dsbenhmoi.removeAt(i);
            qDebug() << "thao bo vi tri: " << i;
        }
    }
}


void tracuuPhieuHen::on_ma_bn_textChanged(const QString &arg1)
{
    this->thuocModel.clear();
}

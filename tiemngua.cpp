#include "tiemngua.h"
#include "ui_tiemngua.h"
#include <QMessageBox>
#include <QTime>
tiemngua::tiemngua(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tiemngua)
{
    ui->setupUi(this);
    //this->update();
    stt = new managerSTT("tiemngua");
    ngay = QDate::currentDate();
    this->updateDScho();
    ui->danhsanhcho->setModel(&danhsachchomodel);
    ui->tableView->setModel(&dsthuoc);
    ui->treeView_ngayhen->setModel(&item_ngayhen);
    ui->danhsachbenh->setModel(&danhsachbenh);
}

tiemngua::~tiemngua()
{
    delete ui;
}

void tiemngua::updateMainContent(int stt)
{
    item_ngayhen.clear();
    query.exec("select phieu_tiem.ma_phieu,stt,phieu_tiem.ma_bn,ma_hd from hoa_don left join phieu_tiem on phieu_tiem.ma_phieu = hoa_don.ma_phieu where date(ngay_lap) = current_date and stt ='"+QString::number(stt) +"'");
    if(query.next()){
        ui->pushButton_2->setEnabled(true);
        maphieu = query.value(0).toString();
        ma_hoadon = query.value(3).toString();
        ma_bn = query.value(2).toString();
        this->infobenh(maphieu,ma_bn);
        this->infothuoc(maphieu,ma_bn);
    }else{
        QMessageBox invali;
        invali.setText("Chua co benh nhan nao trong phong doi");
        invali.exec();
        ui->pushButton_2->setEnabled(false);
        qDebug() << query.lastError();
    }
    query.exec("delete from bo_qua where stt_ = '"+QString::number(stt)+"'");
}
/*
 * updateMainContent chia la 2 nhanh,
 * nhanh 1: truy van den nguoi benh bi benh gi
 * nhanh 2: truy van loai thuoc su dung
*/
void tiemngua::infobenh(QString maphieu, QString mabn)
{

    strquery = "select ten, co_benh.cs_tim, co_benh.cs_ha, benh.ten_benh, co_benh.chu_y,tt_benh_nhan.ma_bn from phieu_tiem \
left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn \
left join co_benh on co_benh.ma_bn = tt_benh_nhan.ma_bn \
left join benh on benh.ma_benh = co_benh.ma_benh where phieu_tiem.ma_phieu ='" +maphieu+"' limit 1";
    query.exec(strquery);
    if(query.next()){
        ui->ten->setText(query.value(0).toString());
        ui->cstim->setText(query.value(1).toString());
        ui->csha->setText(query.value(2).toString());
        ui->chuy->setText(query.value(4).toString());
        //ui->ngaybd->setDate(query.value(5).toDate());
        strquery = "select distinct benh.ten_benh from co_benh left join benh on benh.ma_benh = co_benh.ma_benh where co_benh.ma_bn ='" +mabn+"'";
        danhsachbenh.setQuery(strquery);
    }
}
void tiemngua::infothuoc(QString maphieu, QString mabn)
{
    dsthuoc.setQuery("select thuoc.ten_thuoc,lieu_dung,thuoc.ma_thuoc from phieu_tiem \
                     right join tiem on tiem.ma_phieu = phieu_tiem.ma_phieu \
                     left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc \
                     left join do_tuoi on do_tuoi.ma_dotuoi =thuoc.ma_dotuoi where phieu_tiem.ma_phieu ='"+maphieu+"'");
    //hien thi danh dach ngay hen cua tung thuoc
    for(int i=0; i< dsthuoc.rowCount();i++)
    {
        ma_thuoc = dsthuoc.index(i,2).data().toString();
        stt_lieu = this->tinhSoTTLieu(ma_thuoc,mabn);
        item_ngayhen.appendRow(this->prepareRow(dsthuoc.index(i,0).data().toString(),this->tinh_ngayTaiHen(ma_thuoc,stt_lieu),stt_lieu));
    }
}
/*hien thi cac mui tiem da tiem va ngay tiem*/
void tiemngua::showMuiTiem(QString ma_bnI, QString mat){
    querymodel.setQuery(" select tiem.ma_thuoc from tiem left join tt_benh_nhan on tt_benh_nhan.ma_bn = tiem.ma_bn \
                        left join phieu_tiem on phieu_tiem.ma_phieu = tiem.ma_phieu where \
                        phieu_tiem.ngay_tiem is not null and phieu_tiem.ma_bn = '"+ma_bnI+"' and tiem.ma_thuoc = '"+mat+"'");
    //ui->treeView->setModel(&querymodel);

}


void tiemngua::on_pushButton_2_clicked()
{
    /*
     * Nut tiep theo luu thong tin ngay tiem,
     * */
    //cap nhat ngay tiem cho bang "tiem"
    query.exec("select ma_thuoc from tiem where ma_phieu ='"+maphieu+"'");
    while(query.next())
    {
        ma_thuoc = query.value(0).toString();
        stt_lieu = this->tinhSoTTLieu(ma_thuoc,ma_bn);
        ngaytaihen = this->tinh_ngayTaiHen(ma_thuoc,stt_lieu);
        if(ngaytaihen =="-1")
            ngaytaihen = "Du lieu";
        query_tmp.exec("update tiem set ngay_tiem = current_date, stt_lieu = '"+stt_lieu+"',ngay_hen_kt = '"+ ngaytaihen+ "' where ma_phieu = '"+maphieu+"'");
        qDebug() << query_tmp.lastError().text();
    }
    query.exec("update tt_benh_nhan set da_tiemlandau = TRUE where ma_bn = '"+ma_bn+"'");
    if(!query.exec("update hoa_don set da_tiem= TRUE where ma_hd = '"+ma_hoadon+"'"))
        qDebug() << query.lastError().text();
    else{
        this->cleanFroms();
        //drop cac bang duoc cap nhat trong bang bo_qua
        this->updateDScho();
        this->setcurentidx();
    }
}

void tiemngua::on_pushButton_clicked()
{
    /*
     *Bo qua ghi thong tin ma hd vao bang bo_qua
    */
    MaHD = "-1";
    query.exec("select ma_hd,ma_phieu from hoa_don where ma_phieu = '"+maphieu+"'");
    if(query.next())
    {
        MaHD = query.value(0).toString();
        qDebug() << "Ma hd" << MaHD;
        query.exec("insert into bo_qua values('"+ MaHD +"','"+QString::number(stt->getcurrentindex())+"',current_date())");
        this->cleanFroms();
        this->updateMainContent(stt->next());
    }else{
        qDebug() << query.lastError().text();
    }
    this->cleanFroms();
}

void tiemngua::on_actionChon_nguoi_khong_theo_tt_triggered()
{
    danhSachBoQua xemds;
    xemds.exec();
}
/*
 * Ham viet su kien khi nguoi dung nhan nut tren ban phim
*/
void tiemngua::keyReleaseEvent(QKeyEvent *e)
{
}
/*
 * nhan tin hieu tu danhSachBoQua
*/
void tiemngua::receivers_stt(QString stt)
{
    qDebug() << "Da nhap stt la: "<<stt;
    this->updateMainContent(stt.toInt());
}

void tiemngua::getID()
{
}

void tiemngua::setcurentidx()
{
    row = stt->getcurrentindex();
    col = 0;
    idx  = ui->danhsanhcho->model()->index(row,col);
    ui->danhsanhcho->selectionModel()->select(idx, QItemSelectionModel::Select);
    ui->danhsanhcho->setCurrentIndex(idx);
    ui->danhsanhcho->setFocus();
    //ui->danhsanhcho->clicked(idx);
}

void tiemngua::on_danhsanhcho_clicked(const QModelIndex &index)
{

    if(index.isValid())
    {
            stt->setIDX(index.row());
            this->updateMainContent(this->danhsachchomodel.index(index.row(),0).data().toInt());
}
}

void tiemngua::on_tableView_clicked(const QModelIndex &index)
{
            this->showMuiTiem(ma_bn,this->dsthuoc.index(index.row(),2).data().toString());
}
void tiemngua::updateDScho()
{
    danhsachchomodel.setQuery("select hoa_don.stt,tt_benh_nhan.ten from hoa_don \
                              left join phieu_tiem on phieu_tiem.ma_phieu = hoa_don.ma_phieu \
                              left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn \
                              where hoa_don.ngay_lap = current_date  and hoa_don.da_tiem is null");
}
QString tiemngua::tinh_ngayTaiHen(QString mathuoc,QString sttlieu)
{
    /*sua lai o day sl_nhac_lai tinh truc tiep ben bang lich hen*/
    query_ham.exec("select so_ngay,sl_nhac_lai from thuoc right join lich_hen on lich_hen.ma_thuoc = thuoc.ma_thuoc where lan_thu = '"+sttlieu+"' and thuoc.ma_thuoc = '"+mathuoc+"'" );
    //qDebug() << query_ham.lastQuery();
    if(query_ham.next())
    {
        sl_nhac_lai = query_ham.value(1).toInt();
        if(sl_nhac_lai > 0){
            chu_ky = query_ham.value(0).toInt();
            return ngay_hen.currentDate().addDays(chu_ky).toString("dd-MM-yyyy");
        }
    }
    else
        return "-1";
}
void tiemngua::capnhatPhieuTiem()
{
}
QString tiemngua::tinhSoTTLieu(QString mathuoc,QString mabn)
{
    query_ham.exec("select count(ngay_tiem) from tiem where ma_bn ='"+mabn+"' and ma_thuoc ='"+mathuoc+"' group by ma_bn");
    if(query_ham.next())
    {
        return query_ham.value(0).toString();
    }else{
        return "0";
    }

}

QList<QStandardItem *> tiemngua::prepareRow(const QString &first,
                                                const QString &second,
                                                const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}

void tiemngua::cleanFroms()
{
    ui->chuy->clear();
    ui->csha->clear();
    ui->cstim->clear();
}

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
    //this->initializeModel(&muitiem);
    //ui->tableView->setModel(&muitiem);
    ui->tableView->setModel(&dsthuoc);
    ui->treeView_ngayhen->setModel(&item_ngayhen);
}

tiemngua::~tiemngua()
{
    delete ui;
}
/*truy van hoa don cung voi thong tin thuoc, cap nhat vao
 * statusBar()
*/
//void tiemngua::updatebar(){
//    QString queryhd ="select hoa_don.stt,ten,tiem_thuoc.ma_thuoc from `hoa_don` left join phieu_tiem on \
//hoa_don.ma_phieu = phieu_tiem.ma_phieu left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn \
//left join tiem_thuoc on tiem_thuoc.ma_phieu = phieu_tiem.ma_phieu where date(ngay_lap) = current_date order by stt limit 2 offset 1";
//    query.exec(queryhd);
//    if(query.next())
//    {
//        thongbao = "STT ke tiep: " + query.value(0).toString() + " | Ten: " + query.value(1).toString() + " | Ma thuoc: "+query.value(2).toString();
//        ui->statusbar->showMessage(thongbao);
//    }
//}
/*
 * cap nhat noi dung cho khung chuong trinh
*/
void tiemngua::updateMainContent(int stt)
{
    query.exec("select phieu_tiem.ma_phieu,stt,phieu_tiem.ma_bn,ma_hd from hoa_don left join phieu_tiem on phieu_tiem.ma_phieu = hoa_don.ma_phieu where date(ngay_lap) = current_date and stt ='"+QString::number(stt) +"'");
    if(query.next()){
        ui->pushButton_2->setEnabled(true);
        maphieu = query.value(0).toString();
        ma_hoadon = query.value(3).toString();
        ma_bn = query.value(2).toString();
        this->infobenh(maphieu);
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
void tiemngua::infobenh(QString maphieu)
{
    QString strquery;
    strquery = "select ten, co_benh.cs_tim, co_benh.cs_ha, benh.ten_benh, co_benh.chu_y from phieu_tiem \
left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn \
left join co_benh on co_benh.ma_bn = tt_benh_nhan.ma_bn \
left join benh on benh.ma_benh = co_benh.ma_benh where phieu_tiem.ma_phieu ='" +maphieu+"' limit 1";
    query.exec(strquery);
    if(query.next()){
        ui->ten->setText(query.value(0).toString());
        ui->cstim->setText(query.value(1).toString());
        ui->csha->setText(query.value(2).toString());
        ui->bibenh->setText(query.value(3).toString());
        ui->chuy->setText(query.value(4).toString());
        //ui->ngaybd->setDate(query.value(5).toDate());
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
        item_ngayhen.appendRow(this->prepareRow(dsthuoc.index(i,0).data().toString(),this->tinh_ngayTaiHen(ma_thuoc),this->tinhSoTTLieu(ma_thuoc,mabn)));
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
        query_tmp.exec("update tiem set ngay_tiem = current_date, stt_lieu = '"+this->tinhSoTTLieu(ma_thuoc,ma_bn)+"',ngay_hen_kt = '"+ this->tinh_ngayTaiHen(ma_thuoc)+ "' where ma_phieu = '"+maphieu+"'");
    }
    qDebug() << query.lastError().text();
    qDebug() << query_tmp.lastError().text();
    query.exec("update tt_benh_nhan set da_tiemlandau = TRUE where ma_bn = '"+ma_bn+"'");
    if(!query.exec("update hoa_don set da_tiem= TRUE where ma_hd = '"+ma_hoadon+"'"))
        qDebug() << query.lastError().text();
    this->cleanFroms();
    //danhsachchomodel.setQuery("select * from hoa_don left join phieu_tiem on phieu_tiem.ma_phieu = hoa_don.ma_phieu where ngay_tiem is null");
    //drop cac bang duoc cap nhat trong bang bo_qua
    this->updateDScho();
    this->setcurentidx();
    this->updateMainContent(ui->danhsanhcho->model()->index(ui->danhsanhcho->currentIndex().row(),0).data().toInt());
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
void tiemngua::cleanFroms()
{
    ui->ten->setText("");
    ui->csha->setText("");
    ui->cstim->setText("");
    ui->tenthuoc->setText("");
    ui->dungtich->setText("");
    ui->hieuluc->setText("");
    ui->dotuoi->setText("");
    ui->lieudung->setText("");
    ui->chuy->setText("");
    querymodel.setQuery(NULL);
    //ui->tableView->setModel(NULL);
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
    if(QApplication::keyboardModifiers() && Qt::ControlModifier && e->key() == Qt::Key_Z )//ctrl+z
    {
        dialog_jumStt *jum;
        jum = new dialog_jumStt();
        connect(jum,SIGNAL(setStt(QString)),this,SLOT(receivers_stt(QString)));
        jum->exec();
    }

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
    //qDebug() << ui->treeView->currentIndex().row();
}

void tiemngua::setcurentidx()
{
    row = stt->getcurrentindex();
    col = 0;
    idx  = ui->danhsanhcho->model()->index(row,col);
    ui->danhsanhcho->selectionModel()->select(idx, QItemSelectionModel::Select);
    ui->danhsanhcho->setCurrentIndex(idx);
    ui->danhsanhcho->setFocus();
    ui->danhsanhcho->clicked(idx);
}

void tiemngua::on_danhsanhcho_clicked(const QModelIndex &index)
{
    this->updateMainContent(this->danhsachchomodel.index(index.row(),0).data().toInt());
    stt->setIDX(this->danhsachchomodel.index(index.row(),0).data().toInt());
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
QString tiemngua::tinh_ngayTaiHen(QString mathuoc)
{
    query_ham.exec("select chu_ky,sl_nhac_lai from thuoc where ma_thuoc = '"+mathuoc+"'" );
    if(query_ham.next())
    {
        sl_nhac_lai = query_ham.value(1).toInt();
        if(sl_nhac_lai > 0){
            chu_ky = query_ham.value(0).toInt();
            return ngay_hen.currentDate().addDays(chu_ky).toString();
        }
    }
    else
        return "NULL";
}
void tiemngua::capnhatPhieuTiem()
{



}
QString tiemngua::tinhSoTTLieu(QString mathuoc,QString mabn)
{
    query_ham.exec("select count(ma_thuoc) from tiem where ma_bn ='"+mabn+"' and ma_thuoc ='"+mathuoc+"'");
    if(query_ham.next())
    {
        return query_ham.value(0).toString();
    }
    else{
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

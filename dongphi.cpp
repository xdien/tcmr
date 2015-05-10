#include "dongphi.h"
#include "ui_dongphi.h"

dongphi::dongphi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dongphi)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("qt_sql_default_connection");
    if(!db.driver()->hasFeature(QSqlDriver::EventNotifications))
    {
        qDebug() << "chu y sqlDriver nay khong ho tro notifi";
    }else{
        if(db.driver()->subscribeToNotification("dongphi"))
            connect(db.driver(),SIGNAL(notification(QString)),this,SLOT(capnhatDScho(QString)));
    }
    stt_hd = new managerSTT("dongphi");
    qrmodel.setQuery("select tt_benh_nhan.ma_bn,tt_benh_nhan.ten,tt_benh_nhan.gioi_tinh, phieu_tiem.ma_phieu , hoa_don.ma_hd from phieu_tiem \
                     left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn \
                     left join co_benh on co_benh.ma_bn = tt_benh_nhan.ma_bn \
                     left join hoa_don on hoa_don.ma_phieu = phieu_tiem.ma_phieu \
                     where hoa_don.ma_phieu is null and phieu_tiem.ngay_lap_pt = current_date and co_benh.du_tc is true and co_benh.ngay_kham = current_date ");
    ui->treeView->setModel(&qrmodel);
    //set danh sach thuoc
    ui->treeView_danhsachthuoc->setModel(&danhsachthuoc);
    ui->sotien->setEnabled(false);
    //Dich vu
    ui->treeView_dv->setModel(&dsdichvu);
    /**set header*/
    qrmodel.setHeaderData(0,Qt::Horizontal,"Mã người đk");
    qrmodel.setHeaderData(1,Qt::Horizontal,"Tên");
    qrmodel.setHeaderData(2,Qt::Horizontal,"Giới tính");
    qrmodel.setHeaderData(3,Qt::Horizontal,"Mã Phiếu");


}

dongphi::~dongphi()
{
    delete ui;
}


void dongphi::on_treeView_clicked(const QModelIndex &index)
{
    tongsotien = 0;
    ma_bn = ui->treeView->model()->index(index.row(),0).data().toString();
    ma_phieu = ui->treeView->model()->index(index.row(),3).data().toString();
    danhsachthuoc.setQuery("select distinct thuoc.ten_thuoc,don_gia.gia_ap_dung from phieu_tiem "
                           "right join tiem on tiem.ma_phieu = phieu_tiem.ma_phieu "
                           "left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc "
                           "left join don_gia on thuoc.ma_thuoc = don_gia.ma_thuoc "
                           "where phieu_tiem.ma_phieu = '"+ma_phieu+"'");
    danhsachthuoc.setHeaderData(0,Qt::Horizontal,"Tên thuốc");
    danhsachthuoc.setHeaderData(1,Qt::Horizontal,"Giá");
    query.exec("select sum(distinct don_gia.gia_ap_dung) from phieu_tiem "
               "right join tiem on tiem.ma_phieu = phieu_tiem.ma_phieu "
               "left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc "
               "left join don_gia on thuoc.ma_thuoc = don_gia.ma_thuoc "
               "where phieu_tiem.ma_phieu = '"+ma_phieu+"'");
    if(query.next())
        tongsotien = query.value(0).toInt();
    //load du lieu cho dv
    dsdichvu.setQuery("SELECT ten_phu_phi,gia_ap_dung "
                      "FROM don_gia "
                       "right join (select ma_dm,max(ma_dongia) as ma_dg, max(ngay) from don_gia group by ma_dm) as aa "
                       "on aa.ma_dg = don_gia.ma_dongia right join gom on gom.ma_dm = aa.ma_dm "
                      "left join danh_muc on danh_muc.ma_dm = gom.ma_dm where gom.ma_phieu = '"+ma_phieu+"'");
    dsdichvu.setHeaderData(0,Qt::Horizontal,"Tên phụ phí");
    dsdichvu.setHeaderData(1,Qt::Horizontal,"Giá");

    query.exec("SELECT sum(gia_ap_dung) "
               "FROM don_gia "
               "right join (select ma_dm,max(ma_dongia) as ma_dg, max(ngay) from don_gia group by ma_dm) as aa "
               "on aa.ma_dg = don_gia.ma_dongia right join gom on gom.ma_dm = aa.ma_dm  where gom.ma_phieu = '"+ma_phieu+"'");
    if(query.next())
            tongsotien += query.value(0).toInt();
    else
        qDebug() << query.lastError().text();
    ui->sotien->setText(QString::number(tongsotien));
}

void dongphi::on_pushButton_6_clicked()
{
    //lay ma nhan vien tu bang tam thoi nv_dangnhap
    query.exec("select * from nv_dangnhap");
    if(query.next())
    {
        ma_nv = query.value(0).toString();
        //lay ma_hd sau do tang len 1
        ma_hd = id.getNextIndexCode("hoa_don","HD");
        stt = stt_hd->getcurrentindex();
        QString str ="insert into hoa_don( "
                     "ma_hd, ma_phieu, ma_nv, ngay_lap, so_tien, xac_nhan, stt) "
                     "values('"+ma_hd+"','"+ma_phieu+"','"+ma_nv+"',current_date,'"+ui->sotien->text()+"','0','"+QString::number(stt)+"')";
        if(query.exec(str)){
            stt_hd->next();
            query.exec("NOTIFY tiem");
            this->dsdichvu.clear();
            this->danhsachthuoc.clear();
        }
        else
        qDebug() << query.lastError().text();

        qrmodel.setQuery("select tt_benh_nhan.ma_bn,tt_benh_nhan.ten,tt_benh_nhan.gioi_tinh, phieu_tiem.ma_phieu , hoa_don.ma_hd from phieu_tiem "
                         "left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn "
                         "left join co_benh on co_benh.ma_bn = tt_benh_nhan.ma_bn "
                         "left join hoa_don on hoa_don.ma_phieu = phieu_tiem.ma_phieu "
                         "where hoa_don.ma_phieu is null and phieu_tiem.ngay_lap_pt = current_date and co_benh.du_tc is true and co_benh.ngay_kham = current_date and co_benh.ngay_kham = current_date and co_benh.ngay_kham = current_date");
    }else{
        qDebug() << "Khong the lay ma nhan vien";
    }
}
void dongphi::capnhatDScho(QString notiName)
{
    if(notiName == "dongphi"){
        query.exec("select count(tt_benh_nhan.ma_bn) from phieu_tiem "
                   "left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn "
                   "left join co_benh on co_benh.ma_bn = tt_benh_nhan.ma_bn "
                   "left join hoa_don on hoa_don.ma_phieu = phieu_tiem.ma_phieu "
                   "where hoa_don.ma_phieu is null and phieu_tiem.ngay_lap_pt = current_date and co_benh.du_tc is true "
                   "and co_benh.ngay_kham = current_date");
        if(query.next()){
            emit setThongBao("Số lượng người chờ đóng phí là: " + query.value(0).toString());
        }
        qrmodel.setQuery("select tt_benh_nhan.ma_bn,tt_benh_nhan.ten,tt_benh_nhan.gioi_tinh, phieu_tiem.ma_phieu , hoa_don.ma_hd from phieu_tiem "
                         "left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn "
                         "left join co_benh on co_benh.ma_bn = tt_benh_nhan.ma_bn "
                         "left join hoa_don on hoa_don.ma_phieu = phieu_tiem.ma_phieu "
                         "where hoa_don.ma_phieu is null and phieu_tiem.ngay_lap_pt = current_date and co_benh.du_tc is true "
                         "and co_benh.ngay_kham = current_date and co_benh.ngay_kham = current_date "
                         "and co_benh.ngay_kham = current_date limit 20");
    }

}

void dongphi::on_lineEdit_textChanged(const QString &arg1)
{
    qrmodel.setQuery("select tt_benh_nhan.ma_bn,tt_benh_nhan.ten,tt_benh_nhan.gioi_tinh, phieu_tiem.ma_phieu, "
                     "hoa_don.ma_hd from phieu_tiem "
                     "left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn "
                     "left join co_benh on co_benh.ma_bn = tt_benh_nhan.ma_bn "
                     "left join hoa_don on hoa_don.ma_phieu = phieu_tiem.ma_phieu "
                     "where hoa_don.ma_phieu is null and phieu_tiem.ngay_lap_pt = current_date "
                     "and co_benh.du_tc is true and co_benh.ngay_kham = current_date "
                     "and tt_benh_nhan.ma_bn like '%"+arg1+"' limit 10");
    qDebug()<< qrmodel.lastError().text();
}

void dongphi::on_lineEdit_returnPressed()
{
    if(ui->treeView->model()->index(0,0).isValid())
    {
        idx  = ui->treeView->model()->index(0,0);
        ui->treeView->selectionModel()->select(idx, QItemSelectionModel::Select);
        ui->treeView->setCurrentIndex(idx);
        ma_bn = ui->treeView->model()->index(0,0).data().toString();
        ma_phieu = ui->treeView->model()->index(0,3).data().toString();
        danhsachthuoc.setQuery("select thuoc.ten_thuoc,don_gia.gia from phieu_tiem "
                               "right join tiem on tiem.ma_phieu = phieu_tiem.ma_phieu "
                               "left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc "
                               "left join don_gia on thuoc.ma_thuoc = don_gia.ma_thuoc "
                               "where phieu_tiem.ma_phieu = '"+ma_phieu+"'");
        query.exec("select sum(don_gia.gia) from phieu_tiem "
                   "right join tiem on tiem.ma_phieu = phieu_tiem.ma_phieu "
                   "left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc "
                   "left join don_gia on thuoc.ma_thuoc = don_gia.ma_thuoc "
                   "where phieu_tiem.ma_phieu = '"+ma_phieu+"'");
        if(query.next())
            ui->sotien->setText(query.value(0).toString());
    }
}
void dongphi::closeEvent (QCloseEvent *event)
{

    event->ignore();
}


#include "dongphi.h"
#include "ui_dongphi.h"

dongphi::dongphi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dongphi)
{
    ui->setupUi(this);
    stt_hd = new managerSTT("dongphi");
    qrmodel.setQuery("select tt_benh_nhan.ma_bn,tt_benh_nhan.ten,tt_benh_nhan.gioi_tinh, phieu_tiem.ma_phieu , hoa_don.ma_hd from phieu_tiem \
                     left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn \
                     left join co_benh on co_benh.ma_bn = tt_benh_nhan.ma_bn \
                     left join hoa_don on hoa_don.ma_phieu = phieu_tiem.ma_phieu \
                     where hoa_don.ma_phieu is null and phieu_tiem.ngay_lap_pt = current_date and co_benh.du_tc is true and co_benh.ngay_kham = current_date and co_benh.ngay_kham = current_date");
    ui->treeView->setModel(&qrmodel);
    //set danh sach thuoc
    ui->treeView_danhsachthuoc->setModel(&danhsachthuoc);
    ui->sotien->setEnabled(false);
}

dongphi::~dongphi()
{
    delete ui;
}


void dongphi::on_treeView_clicked(const QModelIndex &index)
{
    ma_bn = ui->treeView->model()->index(index.row(),0).data().toString();
    ma_phieu = ui->treeView->model()->index(index.row(),3).data().toString();
    danhsachthuoc.setQuery("select thuoc.ten_thuoc,don_gia.gia from phieu_tiem \
                           right join tiem on tiem.ma_phieu = phieu_tiem.ma_phieu \
                           left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc \
                           left join don_gia on thuoc.ma_thuoc = don_gia.ma_thuoc \
                           where phieu_tiem.ma_phieu = '"+ma_phieu+"'");
   query.exec("select sum(don_gia.gia) from phieu_tiem \
              right join tiem on tiem.ma_phieu = phieu_tiem.ma_phieu \
              left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc \
              left join don_gia on thuoc.ma_thuoc = don_gia.ma_thuoc \
              where phieu_tiem.ma_phieu = '"+ma_phieu+"'");
            if(query.next())
            ui->sotien->setText(query.value(0).toString());

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
        QString str ="insert into hoa_don( \
                ma_hd, ma_phieu, ma_nv, ngay_lap, so_tien, xac_nhan, stt) \
values('"+ma_hd+"','"+ma_phieu+"','"+ma_nv+"',current_date,'"+ui->sotien->text()+"','0','"+QString::number(stt)+"')";
        if(query.exec(str))
                stt_hd->next();
        else
                qDebug() << query.lastError().text();
        qrmodel.setQuery("select tt_benh_nhan.ma_bn,tt_benh_nhan.ten,tt_benh_nhan.gioi_tinh, phieu_tiem.ma_phieu , hoa_don.ma_hd from phieu_tiem \
                         left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn \
    left join co_benh on co_benh.ma_bn = tt_benh_nhan.ma_bn \
                         left join hoa_don on hoa_don.ma_phieu = phieu_tiem.ma_phieu \
                         where hoa_don.ma_phieu is null and phieu_tiem.ngay_lap_pt = current_date and co_benh.du_tc is true and co_benh.ngay_kham = current_date and co_benh.ngay_kham = current_date and co_benh.ngay_kham = current_date");
    }else{
        qDebug() << "Khong the lay ma nhan vien";
    }
}

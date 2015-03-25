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
    ui->tableView->setModel(&qrmodel);
}

dongphi::~dongphi()
{
    delete ui;
}

void dongphi::on_tableView_doubleClicked(const QModelIndex &index)
{

}

void dongphi::on_tableView_clicked(const QModelIndex &index)
{
    ma_bn = ui->tableView->model()->index(index.row(),0).data().toString();
    qDebug() << "Ma bn la: "<< ma_bn;
    ui->ten->setText(ui->tableView->model()->index(index.row(),1).data().toString());
    ui->sex->setText(ui->tableView->model()->index(index.row(),2).data().toString());
    ma_phieu = ui->tableView->model()->index(index.row(),3).data().toString();
    //lay thong tin thuoc
    query.exec("select thuoc.ten_thuoc,don_gia.gia,benh.ten_benh from phieu_tiem \
               right join tiem on tiem.ma_phieu = phieu_tiem.ma_phieu \
               left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc \
               left join don_gia on thuoc.ma_thuoc = don_gia.ma_thuoc \
               left join phong_ngua on phong_ngua.ma_thuoc = thuoc.ma_thuoc \
               left join benh on benh.ma_benh = phong_ngua.ma_benh where phieu_tiem.ma_phieu = '"+ma_phieu+"'");
    if(query.next())
    {
            //ui->loaithuoc->setText(query.value(0).toString());
            ui->sotien->setText(query.value(1).toString());
            //ui->loaibenh->setText(query.value(2).toString());
      qDebug()<<"thanh cong";
    }

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
        //lay stt tu trong hoa_don sau do tang 1 neu k co thi gan = 0
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

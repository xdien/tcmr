#include "khamsobo.h"
#include "ui_khamsobo.h"

khamsobo::khamsobo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::khamsobo)
{
    ui->setupUi(this);
    stt = new managerSTT();
    this->loaddanhsach_chokham();
    ui->listView_dsCho->setModel(&danhsachCho);
    ui->treeView_benhdk->setModel(&danhsachBenhdk);
    danhsachBenh.setQuery("select ten_benh,ma_benh from benh where la_vx = 'FALSE'");
    ui->treeView_benh->setModel(&danhsachBenh);
    ui->listView_benhduocchon->setModel(&itemModel_benhDChon);
    ui->danhsach_chonthuoc->setModel(&itemModel_thuocDChon);
    this->disableEdit(false);

}

khamsobo::~khamsobo()
{
    delete ui;
}
void khamsobo::loaddanhsach_chokham(){
    danhsachCho.setQuery("select ten,sn,phieu_tiem.ma_phieu,tt_benh_nhan.ma_bn from phieu_tiem left join tt_benh_nhan on tt_benh_nhan.ma_bn = phieu_tiem.ma_bn left join co_benh on co_benh.ma_bn = phieu_tiem.ma_bn where ngay_lap_pt = current_date and du_tc is null");
}

void khamsobo::setcurentidx()
{
    row = stt->getcurrentindex();
    col = 0;
    idx  = ui->listView_dsCho->model()->index(row,col);
    ui->listView_dsCho->selectionModel()->select(idx, QItemSelectionModel::Select);
    ui->listView_dsCho->setCurrentIndex(idx);
    ui->listView_dsCho->setFocus();
    ui->listView_dsCho->clicked(idx);
}

void khamsobo::infoTTbenhNhan(QString ma_phieu)
{

}

void khamsobo::on_pushButton_clicked()
{

    //lay ma benh ra
    query.exec("select * from nv_dangnhap");
    if(query.next())
    {
        ma_nv = query.value(0).toString();
        sodong = itemModel_benhDChon.rowCount();
        if(sodong > 0)
        {
            for(int i = 0; i<sodong;i++)
            {
                ma_benh = itemModel_benhDChon.index(i,1).data().toString();
                query.exec("INSERT INTO co_benh( \
                           ma_benh, ma_bn, ma_nv, cs_tim, cs_ha, chu_y, du_tc, ngay_kham) \
VALUES ('"+ma_benh+"', '"+ ma_bn+ "','"+ma_nv+"', '"+ui->cs_tim->text()+"', '"+ ui->csha->text() +"', '"+ui->chuy->document()->toPlainText()+"', 'TRUE',current_date)");
            }
        }else{
            ma_benh = "1";
            query.exec("INSERT INTO co_benh( \
                       ma_benh, ma_bn, ma_nv, cs_tim, cs_ha, chu_y, du_tc, ngay_kham) \
VALUES ('"+ma_benh+"', '"+ ma_bn+ "','"+ma_nv+"', '"+ui->cs_tim->text()+"', '"+ ui->csha->text() +"', '"+ui->chuy->document()->toPlainText()+"', 'TRUE',current_date)");
        }
        //Nhap vao danh sach thuoc duoc chon
        thuoc_num = itemModel_thuocDChon.rowCount();
        for(int i =0;i<thuoc_num;i++){
            ma_thuoc = itemModel_thuocDChon.index(i,1).data().toString();
            query.exec("insert into tiem values('"+ma_thuoc+"','"+ma_phieu+"','"+ma_nv+"')");
            qDebug()<<query.lastError().text();
        }
        this->loaddanhsach_chokham();
        //tra ve benh nhan ke tiep
        this->setcurentidx();
    }else{
        qDebug() << "Can't get id NHAN_VIEN";
    }

}

void khamsobo::on_listView_dsCho_clicked(const QModelIndex &index)
{
    stt->setIDX(index.row());
    ui->ten->setText(this->danhsachCho.index(index.row(),0).data().toString());
    ngay_sinh = this->danhsachCho.index(index.row(),1).data().toDate();
    do_tuoi = ngay_sinh.daysTo(QDate::currentDate());
    do_tuoi = do_tuoi / 365;
    ma_bn = this->danhsachCho.index(index.row(),3).data().toString();//lay ma benh nhan
    ui->tuoi->setText(QString::number(do_tuoi));
    ma_phieu = this->danhsachCho.index(index.row(),2).data().toString();
    danhsachBenhdk.setQuery("select ten_benh,benh.ma_benh from muon_tiem \
                            left join benh on benh.ma_benh = muon_tiem.ma_benh \
                            where muon_tiem.ma_phieu = '"+ma_phieu+"'");
            this->disableEdit(true);
}

void khamsobo::on_pushButton_3_clicked()
{
//    QDate n1,n2;
//    int tmpp;
//    n1.setDate(1992,06,05);
//    n2.setDate(2012,06,05);
//    tmpp = n2.toJulianDay() - n1.toJulianDay();
//    qDebug() << n1.daysTo(n2);
//    qDebug() << tmpp;
//    qDebug() << QDate::fromJulianDay(tmpp);
    //qDebug() << n2.year();
    QString test;
    test = "KH";
    qDebug() << test.mid(3);//lay gia tri tu vi tri thu 3 tro ve sau

}
void khamsobo::disableEdit(bool state)
{
    ui->csha->setText("");
    ui->cs_tim->setText("");
    ui->chuy->setText("");
    ui->csha->setEnabled(state);
    ui->cs_tim->setEnabled(state);
    ui->chuy->setEnabled(state);
}

void khamsobo::on_treeView_benh_doubleClicked(const QModelIndex &index)
{
    mot = this->danhsachBenh.index(index.row(),0).data().toString(); //lay ten thuoc tu model
    hai = this->danhsachBenh.index(index.row(),1).data().toString();//lay ma thuoc tu moel
    ba = "";
    //itemModel_benhDChon.findItems()
    itemModel_benhDChon.appendRow(this->prepareRow(mot,hai,ba));
}
//add item model
QList<QStandardItem *> khamsobo::prepareRow(const QString &first,
                                                const QString &second,
                                                const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}

void khamsobo::on_khongduak_clicked()
{
    query.exec("select * from nv_dangnhap");
    if(query.next())
    {
        ma_nv = query.value(0).toString();
        sodong = itemModel_benhDChon.rowCount();
        if(sodong > 0)
        {
            for(int i = 0; i<sodong;i++)
            {
                ma_benh = itemModel_benhDChon.index(i,1).data().toString();
                query.exec("INSERT INTO co_benh( \
                           ma_benh, ma_bn, ma_nv, cs_tim, cs_ha, chu_y, du_tc, ngay_kham) \
VALUES ('"+ma_benh+"', '"+ ma_bn+ "','"+ma_nv+"', '"+ui->cs_tim->text()+"', '"+ ui->csha->text() +"', '"+ui->chuy->document()->toPlainText()+"', 'FALSE',current_date)");
            }
        }else{
            ma_benh = "1";
            query.exec("INSERT INTO co_benh( \
                       ma_benh, ma_bn, ma_nv, cs_tim, cs_ha, chu_y, du_tc, ngay_kham) \
VALUES ('"+ma_benh+"', '"+ ma_bn+ "','"+ma_nv+"', '"+ui->cs_tim->text()+"', '"+ ui->csha->text() +"', '"+ui->chuy->document()->toPlainText()+"', 'FALSE',current_date)");
        }
        qDebug()<< query.lastError().text();
        this->loaddanhsach_chokham();
        //tra ve benh nhan ke tiep
        this->setcurentidx();
    }else{
        qDebug() << "Can't get id NHAN_VIEN";
    }
}

void khamsobo::on_treeView_benhdk_clicked(const QModelIndex &index)
{
    ma_benh = this->danhsachBenhdk.index(index.row(),1).data().toString();
    danhsach_goiyThuoc.setQuery("select thuoc.ten_thuoc,do_tuoi.do_tuoi,thuoc.ma_thuoc from benh right join phong_ngua on phong_ngua.ma_benh = benh.ma_benh \
                                left join thuoc on thuoc.ma_thuoc = phong_ngua.ma_thuoc \
            left join do_tuoi on do_tuoi.ma_dotuoi = thuoc.ma_dotuoi  where benh.ma_benh = '"+ma_benh+"'");
            ui->treeView_thuocgoiY->setModel(&danhsach_goiyThuoc);
}

void khamsobo::on_treeView_thuocgoiY_clicked(const QModelIndex &index)
{
    mot = this->danhsach_goiyThuoc.index(index.row(),0).data().toString(); //lay ten thuoc tu model
    hai = this->danhsach_goiyThuoc.index(index.row(),2).data().toString();//lay ma thuoc tu moel
    ba = "";
    //itemModel_benhDChon.findItems()
    itemModel_thuocDChon.appendRow(this->prepareRow(mot,hai,ba));
}

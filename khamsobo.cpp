#include "khamsobo.h"
#include "ui_khamsobo.h"

khamsobo::khamsobo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::khamsobo)
{
    ui->setupUi(this);
    stt = new managerSTT("khamsobo");
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
    danhsachCho.setQuery("select stt,ten,sn,ma_bn from tt_benh_nhan where ngay_lap = current_date and lap_phieu is null");
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
    if(query.next() && ui->csha->text().toInt() > 0)
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
        //lap phieu tiem
        ma_phieu = id.getNextIndexCode("phieu_tiem","PT");
        //query.exec("")
        if(query.exec("INSERT INTO phieu_tiem( ma_phieu, ma_bn, ma_nv, ngay_lap_pt, phieu_tiem_lan_dau) VALUES ('"+ ma_phieu +"', '"+ma_bn+"', '"+ma_nv+"', current_date)"))
        {
            //Nhap vao danh sach thuoc duoc chon
            thuoc_num = itemModel_thuocDChon.rowCount();
            for(int i =0;i<thuoc_num;i++){
                ma_thuoc = itemModel_thuocDChon.index(i,1).data().toString();
                query.exec("insert into tiem values('"+ma_thuoc+"','"+ma_phieu+"','"+ma_nv+"','"+ma_bn+"')");
                qDebug()<<query.lastError().text();
            }
            //query.exec("")
            if(!query.exec("update tt_benh_nhan set lap_phieu = 'TRUE' where ma_bn = '"+ma_bn+"'"))
                qDebug() << query.lastError().text();
            this->loaddanhsach_chokham();
            //tra ve benh nhan ke tiep
            this->setcurentidx();
        }else{
            qDebug() << "khong the lap phieu: " << query.lastError().text();
        }
    }else{
        qDebug() << "Can't get id NHAN_VIEN";
    }

}

void khamsobo::on_listView_dsCho_clicked(const QModelIndex &index)
{
    stt->setIDX(index.row());
    ui->ten->setText(this->danhsachCho.index(index.row(),1).data().toString());
    ngay_sinh = this->danhsachCho.index(index.row(),2).data().toDate();
    do_tuoi = ngay_sinh.daysTo(QDate::currentDate());
    do_tuoi = do_tuoi / 365;
    ma_bn = this->danhsachCho.index(index.row(),3).data().toString();//lay ma benh nhan
    ui->tuoi->setText(QString::number(do_tuoi));
    ma_phieu = this->danhsachCho.index(index.row(),2).data().toString();
    danhsachBenhdk.setQuery("select ten_benh,benh.ma_benh from muon_tiem left join benh on benh.ma_benh = muon_tiem.ma_benh \
                            where muon_tiem.ma_bn = '"+ma_bn+"'");
            this->disableEdit(true);
}

void khamsobo::on_pushButton_3_clicked()
{
    QString test;
    test = "KH_100";
    QDate d1,d2;
    d1.setDate(1992,2,1);

    qDebug() << d1.addDays(45).toString("yyyy-MM-dd") ;

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
void khamsobo::lapphieuHen(QString mabn, QString manv,QString maPHIEUTIEM, QString mabenh)
{
    ma_phieuhen = id.getNextIndexCode("phieu_hen","PH");
    query.exec("INSERT INTO phieu_hen( \
               ma_phieuhen, ma_bn, ma_nv, ma_phieu, ma_benh, mui_thu, ngay_tai_hen, \
               ngay_lap, khong_the_tiem) \
       VALUES ('"+ma_phieuhen+"', '"+mabn+"', '"+manv+"', '"+maPHIEUTIEM+"', '"+mabenh +"', ?, ?, current_date, ?)");
}
QString khamsobo::tinh_ngayTaiHen(QString mathuoc)
{
    query.exec("select chu_ky from thuoc where ma_thuoc = '"+mathuoc+"'" );
    if(query.next())
    {
        chu_ky = query.value(0).toInt();
        return ngay_hen.currentDate().addDays(chu_ky).toString();
    }
    else
        return "2015-01-01";
}

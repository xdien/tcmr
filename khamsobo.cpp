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
    ui->treeView_DSPhiChon->setModel(&itemModel_dichvu);
    ui->treeView_dichVu->setModel(&danhsachDV);
    ui->treeView_thuocgoiY->setModel(&danhsach_goiyThuoc);
    danhsachDV.setQuery("select ten_phu_phi,ma_dm from danh_muc");
    this->disableEdit(false);
    //lay ket noi database hien tai
    db = QSqlDatabase::database("qt_sql_default_connection");
    if(!db.driver()->hasFeature(QSqlDriver::EventNotifications))
    {
        qDebug() << "chu y sqlDriver nay khong ho tro notifi";
    }else{
        db.driver()->subscribeToNotification("khamsobo");
        connect(db.driver(),SIGNAL(notification(QString)),this,SLOT(codkMoi(QString)));
    }
    /*setheader*/
    danhsachBenh.setHeaderData(0,Qt::Horizontal,"Tên bệnh");
    danhsachBenh.setHeaderData(1,Qt::Horizontal,"Mã bệnh");
    danhsachDV.setHeaderData(0,Qt::Horizontal, "Tên dịch vụ");
    danhsachDV.setHeaderData(1,Qt::Horizontal,"Mã DV");
}

khamsobo::~khamsobo()
{
    delete stt;
    delete ui;
}
void khamsobo::loaddanhsach_chokham(){
    danhsachCho.setQuery("select stt,ten,age(sn),ma_bn from tt_benh_nhan where ngay_lap = current_date and lap_phieu is null order by stt limit 20");
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


void khamsobo::on_pushButton_clicked()
{

    //lay ma benh ra
    query.exec("select * from nv_dangnhap");
    if(query.next() && ui->csha->text().toInt() > 0)
    {
        if(ui->checkBox_khogtimdc->isChecked())
            co_benh = "FALSE";
        else
            co_benh = "TRUE";
        ma_nv = query.value(0).toString();
        sodong = itemModel_benhDChon.rowCount();
        if(sodong > 0)
        {
            for(int i = 0; i<sodong;i++)
            {
                ma_benh = itemModel_benhDChon.index(i,1).data().toString();
                query.exec("INSERT INTO co_benh( \
                           ma_benh, ma_bn, ma_nv, cs_tim, cs_ha, chu_y, du_tc, ngay_kham) \
                        VALUES ('"+ma_benh+"', '"+ ma_bn+ "','"+ma_nv+"', '"+ui->cs_tim->text()+"', '"+ ui->csha->text() +"', '"+ui->chuy->document()->toPlainText()+"', '"+co_benh+"',current_date)");
            }
        }else{
            ma_benh = "BH_00000000";
            query.exec("INSERT INTO co_benh( \
                       ma_benh, ma_bn, ma_nv, cs_tim, cs_ha, chu_y, du_tc, ngay_kham)\
                    VALUES ('"+ma_benh+"', '"+ ma_bn+ "','"+ma_nv+"', '"+ui->cs_tim->text()+"', '"+ ui->csha->text() +"', '"+ui->chuy->document()->toPlainText()+"', "+co_benh+",current_date)");
        }
        query.exec("UPDATE co_benh "
                   "SET ngay_kham=current_date "
                   "WHERE ma_bn = '"+ma_bn+"'");
        //lap phieu tiem
        ma_phieu = id.getNextIndexCode("phieu_tiem","PT");
        if(query.exec("INSERT INTO phieu_tiem( ma_phieu, ma_bn, ma_nv, ngay_lap_pt) VALUES "
                      "('"+ ma_phieu +"', '"+ma_bn+"', '"+ma_nv+"', current_date)"))
        {
            //Nhap vao danh sach thuoc duoc chon
            thuoc_num = itemModel_thuocDChon.rowCount();
            for(int i =0;i<thuoc_num;i++){
                ma_thuoc = itemModel_thuocDChon.index(i,1).data().toString();
                query.exec("INSERT INTO tiem(\
                           ma_thuoc, ma_phieu, ma_nv, ma_bn) values('"+ma_thuoc+"','"+ma_phieu+"','"+ma_nv+"','"+ma_bn+"')");
            }
            if(!query.exec("update tt_benh_nhan set lap_phieu = 'TRUE' where ma_bn = '"+ma_bn+"'"))
            {
                qDebug() << query.lastError().text();
            }else{
                //Cap nhat cac phu phi
                thuoc_num = itemModel_dichvu.rowCount();
                for(int i =0;i<thuoc_num;i++)
                {
                    query.exec("INSERT INTO gom( "
                               "ma_phieu, ma_dm) "
                               "VALUES ('"+ma_phieu+"', '"+itemModel_dichvu.index(i,1).data().toString()+"')");
                }
                //xoa cai lineedit
                itemModel_benhDChon.clear();
                itemModel_dichvu.clear();
                itemModel_thuocDChon.clear();
                danhsach_goiyThuoc.clear();
                danhsachBenhdk.clear();
            }
            query.exec("NOTIFY dongphi");
            //cap nhat lai benh dang ky
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
    //kiem tra co phai la benh nhanh moi or cu truy van thuoc khac nhau
    if(index.isValid())
    {
        ma_bn = this->danhsachCho.index(index.row(),3).data().toString();//lay ma benh nhan
        query.exec("select * from tt_benh_nhan where tai_hen is true");
        if(query.next())
            this->loadchitietBN_C(index);
        else{
            this->loadchitietBN_M(index);
        }
    }
}

void khamsobo::on_pushButton_3_clicked()
{
    //them thuoc theo ma
    query.exec("select ma_thuoc,ten_thuoc from thuoc where ma_thuoc  like '%"+ui->lineEdit_mathuoc->text()+"'");
    if(query.next())
    {
        //tim thay ma thuoc them vao danh sach
        mot = query.value(1).toString(); //lay ten thuoc tu model
        hai = query.value(0).toString();//lay ma thuoc tu moel
        ba = "";
        itemModel_thuocDChon.appendRow(this->prepareRow(mot,hai,ba));
    }else
    {
        //khong tim thay ma thuoc hien thi thong bao
        ui->label_kq->setText("Khong tim thay thuoc");
    }
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
    danhsach_goiyThuoc.setQuery("select thuoc.ten_thuoc,do_tuoi.do_tuoi,thuoc.ma_thuoc from benh right join phong_ngua on phong_ngua.ma_benh = benh.ma_benh "
                                "left join thuoc on thuoc.ma_thuoc = phong_ngua.ma_thuoc "
                                "left join do_tuoi on do_tuoi.ma_dotuoi = thuoc.ma_dotuoi  where benh.ma_benh = '"+ma_benh+"'");
    danhsach_goiyThuoc.setHeaderData(0,Qt::Horizontal,"Tên thuốc");
    danhsach_goiyThuoc.setHeaderData(0,Qt::Horizontal,"Độ tuổi");
    danhsach_goiyThuoc.setHeaderData(0,Qt::Horizontal,"Mã thuốc");
}

void khamsobo::on_treeView_thuocgoiY_clicked(const QModelIndex &index)
{
    ma_dv =danhsach_goiyThuoc.index(index.row(),2).data().toString();
    tmp = itemModel_thuocDChon.findItems(ma_dv,Qt::MatchExactly,1);
    if(tmp.count() <= 0)
    {
        mot = this->danhsach_goiyThuoc.index(index.row(),0).data().toString(); //lay ten thuoc tu model
        hai = this->danhsach_goiyThuoc.index(index.row(),2).data().toString();//lay ma thuoc tu moel
        ba = "";
        itemModel_thuocDChon.appendRow(this->prepareRow(mot,hai,ba));
    }

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
void khamsobo::loadchitietBN_M(QModelIndex indexx)
{
    stt->setIDX(indexx.row());
    ui->ten->setText(this->danhsachCho.index(indexx.row(),1).data().toString());
//    ngay_sinh = this->danhsachCho.index(indexx.row(),2).data().toDate();
//    do_tuoi = ngay_sinh.daysTo(QDate::currentDate());
//    do_tuoi = do_tuoi / 365;
//    ui->tuoi->setText(QString::number(do_tuoi));
    ui->tuoi->setText(this->danhsachCho.index(indexx.row(),2).data().toString());
    //ma_phieu = this->danhsachCho.index(indexx.row(),2).data().toString();
    danhsachBenhdk.setQuery("select ten_benh,benh.ma_benh from muon_tiem left join benh on benh.ma_benh = muon_tiem.ma_benh "
                            "where muon_tiem.ma_bn = '"+ma_bn+"'");
    this->disableEdit(true);
    danhsachBenhdk.setHeaderData(0,Qt::Horizontal,"Tên bệnh");
    danhsachBenhdk.setHeaderData(1,Qt::Horizontal,"Mã bệnh");
}

void khamsobo::loadchitietBN_C(QModelIndex indexx)
{
    itemModel_thuocDChon.clear();
    stt->setIDX(indexx.row());
    ui->ten->setText(this->danhsachCho.index(indexx.row(),1).data().toString());
    ngay_sinh = this->danhsachCho.index(indexx.row(),2).data().toDate();
    do_tuoi = ngay_sinh.daysTo(QDate::currentDate());
    do_tuoi = do_tuoi / 365;
    ui->tuoi->setText(QString::number(do_tuoi));
    //ma_phieu = this->danhsachCho.index(indexx.row(),2).data().toString();
    danhsachBenhdk.setQuery("select ten_benh,benh.ma_benh from muon_tiem left join benh on benh.ma_benh = muon_tiem.ma_benh "
                            "where muon_tiem.ma_bn = '"+ma_bn+"'");
    this->disableEdit(true);
    danhsachBenhdk.setHeaderData(0,Qt::Horizontal,"Tên bệnh");
    danhsachBenhdk.setHeaderData(1,Qt::Horizontal,"Mã bệnh");
    //           itemModel_thuocDChon.appendRow(this->prepareRow());
    //lay danh sach thuoc ngay tai hen
    query.exec("select thuoc.ten_thuoc,thuoc.ma_thuoc from tiem left join thuoc on thuoc.ma_thuoc = tiem.ma_thuoc where ngay_dk_tai_hen = current_date and ma_bn = '"+ma_bn+"'");
    while(query.next()){
        mot =  query.value(0).toString();//lay ten thuoc tu model
        hai = query.value(1).toString();//lay ma thuoc tu moel
        ba = "";
        //itemModel_benhDChon.findItems()
        itemModel_thuocDChon.appendRow(this->prepareRow(mot,hai,ba));
    }
    //itemModel_thuocDChon.
}

void khamsobo::on_pushButton_2_clicked()
{
    //xoa mot thuoc trong danh sach
    itemModel_thuocDChon.removeRow(ui->danhsach_chonthuoc->currentIndex().row());
}

void khamsobo::codkMoi(QString notiName)
{
    if(notiName == "khamsobo"){
        query_notify.exec("select count(ma_bn) from tt_benh_nhan where ngay_lap = current_date and lap_phieu is null");
        if(query_notify.next())
        {
            //neu co nhieu hon 1 benh nhan thi k lam gi
            qDebug() << query_notify.value(0).toInt();
            if(query_notify.value(0).toInt() == 1 )
            {
                //set idex dau tien va click
                row = 0;
                idx  = ui->listView_dsCho->model()->index(row,col);
                ui->listView_dsCho->selectionModel()->select(idx, QItemSelectionModel::Select);
                ui->listView_dsCho->setCurrentIndex(idx);
                ui->listView_dsCho->setFocus();
                //ui->listView_dsCho->clicked(idx);
            }
            //gioi han 20
            if(query_notify.value(0).toInt() <= 20 )
            {
                this->loaddanhsach_chokham();
            }
            emit setThongBao(QString::fromUtf8("Số lượng người chờ khám là :")+query_notify.value(0).toString());
        }
    }
}

void khamsobo::on_treeView_dichVu_clicked(const QModelIndex &index)
{
    ma_dv =danhsachDV.index(index.row(),1).data().toString();
    tmp = itemModel_dichvu.findItems(ma_dv,Qt::MatchExactly,1);
    if(tmp.count() <= 0)
    {
        itemModel_dichvu.appendRow(this->prepareRow(danhsachDV.index(index.row(),0).data().toString(),danhsachDV.index(index.row(),1).data().toString(),""));
        //itemtDSbenh.appendRow(this->prepareRow(danhsachgoiYBenh.index(index.row(),0).data().toString(),ma_benh,""));
    }

}

void khamsobo::on_treeView_benh_clicked(const QModelIndex &index)
{

}

#include "dangkyphieutiem.h"
#include "ui_dangkyphieutiem.h"


Dangkyphieutiem::Dangkyphieutiem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dangkyphieutiem)
{
    ui->setupUi(this);
    //cho combox thanh pho;
    cmb_tp = new QSqlQueryModel();
    cmb_tp->setQuery("select name,provinceid from province");
    ui->comboBox_tp->setModel(cmb_tp);
    //load du lieu cho bang benh
    list_benh = new QSqlQueryModel();
    list_benh->setQuery("select ten_benh,ma_benh from benh where la_vx = '1'");
    ui->listView_benh->setModel(list_benh);
    //load du lieu rong cho thuoc;
    table_thuoc = new QSqlQueryModel();
    //ui->tableView_loaithuoc->setModel(table_thuoc);
    ui->listView_duocchon->setModel(&itemModel);
    //load do tuoi

    stt = new managerSTT("dangkytt");
}

Dangkyphieutiem::~Dangkyphieutiem()
{
    delete ui;
    delete list_benh;
    delete cmb_tp;
    delete stt;
    delete table_thuoc;
}

void Dangkyphieutiem::on_comboBox_tp_currentIndexChanged(int index)
{
    ui->comboBox_qh->clear();
//    query.exec("select * from district where provinceid = '"+ui->comboBox_tp->itemData(index).toString()+"'");
    //lay gia tri tu model khong lay gia tri tu cmb_
    query.exec("select * from district where provinceid = '"+ui->comboBox_tp->model()->index(index,1).data().toString() +"'");
    while (query.next()) {
        ui->comboBox_qh->addItem(query.value(1).toString(),query.value(0).toString());
    }
    //them gia tri rong
    ui->comboBox_qh->addItem("");
}

void Dangkyphieutiem::on_comboBox_qh_currentIndexChanged(int index)
{
    QSqlQuery xaphuong;
    ui->comboBox_xp->clear();
    xaphuong.exec("SELECT * FROM ward where districtid = '"+ui->comboBox_qh->itemData(index).toString()+"'");
    while(xaphuong.next())
    {
        ui->comboBox_xp->addItem(xaphuong.value(1).toString(),xaphuong.value(0).toString());
    }
    //them fia tri rong
    ui->comboBox_xp->addItem("");
}
QString Dangkyphieutiem::thuocdiachi(QString nhapvao)
{
    int len_address;
    len_address = nhapvao.length();
    switch (len_address) {
    case 2:
        return "province";
        break;
    case 3:
        return "district";
        break;
    case 5:
        return "ward";
        break;
    default:
        return "province";
        break;
    }
}
/*
 * setcombox cho dia chi dua vaodo dai ma dia chi nhap vao
*/
void Dangkyphieutiem::setcombobox(QString madc)
{
    int lent;
    lent = madc.length();
    QString luu, disid;
    switch (lent) {
    case 2:
    {
        ui->comboBox_tp->setCurrentIndex(ui->comboBox_tp->findData(madc));
        ui->comboBox_qh->setCurrentIndex(-1);
        ui->comboBox_xp->setCurrentIndex(-1);
        break;
    }
    case 3:
    {
        query.exec("SELECT * FROM district where districtid = '"+madc+"'");
        while(query.next())
        {
            ui->comboBox_qh->addItem(query.value(1).toString(), query.value(0).toString());
            luu = query.value(4).toString();//luu gia ma tinh thanh
        }

        query.exec("select * from provice where provinceid = '"+luu+"'");
        ui->comboBox_tp->setCurrentIndex(ui->comboBox_tp->findData(luu));
        ui->comboBox_qh->setCurrentIndex(ui->comboBox_qh->findData(madc));
        ui->comboBox_xp->setCurrentIndex(-1);
        break;
    }
    default:
    {
        query.exec("SELECT * FROM ward where wardid = '"+madc+"'");
        while(query.next())
        {
            ui->comboBox_xp->addItem(query.value(1).toString(), query.value(0).toString());
            disid = query.value(4).toString();
        }
        //set gia tri cho qh
        query.exec("select * from district where districtid = '"+disid+"'");
        if(query.next())
        {
            luu = query.value(4).toString();//luu gia ma tinh thanh
        }
        ui->comboBox_tp->setCurrentIndex(ui->comboBox_tp->findData(luu));
        ui->comboBox_qh->setCurrentIndex(ui->comboBox_qh->findData(disid));
        ui->comboBox_xp->setCurrentIndex(ui->comboBox_xp->findData(madc));
        break;
    }
    }
}
/*
 * load cac gia tri mac dinh tu csdl len cac cmb dia chi
*/
void Dangkyphieutiem::loadDefaultarr()
{
    ui->comboBox_xp->clear();
    if(query.next())
    {
        ui->lineEdit_diachi->clear();
        ui->lineEdit_diachi->setText(query.value(1).toString());
        if(query.value(3).isNull())
        {
            setcombobox(query.value(4).toString());
        }
        else
        {
            if(query.value(2).isNull())
            {
                setcombobox(query.value(3).toString());
            }
            else
            {
                setcombobox(query.value(2).toString());
            }
        }
    }
}
void Dangkyphieutiem::loadTP(){
    query.exec("select * from province");
    while(query.next())
    {
        ui->comboBox_tp->addItem(query.value(1).toString(),query.value(0).toString());
        query.next();
        ui->comboBox_tp->addItem(query.value(1).toString(),query.value(0).toString());
        qDebug() << "ads";
    }
}
/*
 * khi chon mot benh se hien thi tuong uog loai thuoc can dung
*/

void Dangkyphieutiem::on_listView_benh_clicked(const QModelIndex &index)
{
    QString aa;
    aa = ui->listView_benh->model()->index(index.row(),1).data().toString();
    table_thuoc->setQuery("select thuoc.ten_thuoc,do_tuoi.do_tuoi,thuoc.ma_thuoc from benh right join phong_ngua on phong_ngua.ma_benh = benh.ma_benh \
left join thuoc on thuoc.ma_thuoc = phong_ngua.ma_thuoc \
left join do_tuoi on do_tuoi.ma_dotuoi = thuoc.ma_dotuoi where benh.ma_benh = '" + aa + "'");
}
/*
 * ham lay gioi tinh tu radio tra ve "nam/nu"
*/
QString Dangkyphieutiem::getSex(){
    if(ui->radioButton->isChecked())
        return "Nam";
    else
        return "None";
    if(ui->radioButton_2->isChecked())
        return "Nu";
    else
        return "None";
}
void Dangkyphieutiem::on_luu_tt_clicked()
{
    //lay ma nv tu table temporary luc dang nhap
    if(ui->ten->text() != ""){
        query.exec("select * from nv_dangnhap");
        if(query.next())
        {
            ma_nv = query.value(0).toString();
            ma_dc = this->getAdrrCode();
            gioitinh = this->getSex();
            ten_bn = ui->ten->text();
            //ma_dt = this->dotuoimode.index(ui->comboBox_dotuoi->currentIndex(),1).data().toString();
            ma_bn = id.getNextIndexCode("tt_benh_nhan","BN");
            QString str;
            str = "INSERT INTO tt_benh_nhan(ma_bn,  ten, gioi_tinh, ma_dc, dc_chi_tiet, sn, stt, ngay_lap, \
                    lap_phieu, da_tiemlandau, tai_hen) values('"+ma_bn+"', '"+ten_bn+"','"+gioitinh+"','"+ma_dc+"','"+ui->lineEdit_diachi->text()+"','"+ui->dateEdit->date().toString("yyyy-MM-dd")+"','"+QString::number(stt->getcurrentindex())+"',current_date,NULL,NULL,NULL)";
                    if(query.exec(str))
            {
                stt->next();
                //tao su kien notify cho khamsobo
                query.exec("NOTIFY khamsobo");
                //xoa thong tin tren lineedit
                ui->lineEdit_diachi->clear();
                ui->ten->clear();
                ui->lineEdit_3->clear();
            }
            else{
                qDebug() << "Loi them tt benh nhan: "<< query.lastError().text();
            }
            thuoc_num = itemModel.rowCount();
            for(int i =0;i<thuoc_num;i++){
                ma_thuoc = itemModel.index(i,1).data().toString();
                if(!query.exec("insert into muon_tiem values('"+ma_thuoc+"','"+ma_bn+"')"))
                    qDebug()<<query.lastError().text();
            }

        }else{
            qDebug() << "Can't get id NHAN_VIEN";
        }
    }
}
QString Dangkyphieutiem::getAdrrCode()
{
    if(ui->comboBox_xp->itemData(ui->comboBox_xp->currentIndex()).toString().isEmpty())
    {
        //neu province khong rong thi do la qh
        if(!ui->comboBox_qh->itemData(ui->comboBox_qh->currentIndex()).toString().isEmpty())
            return ui->comboBox_qh->itemData(ui->comboBox_qh->currentIndex()).toString();
        else
            return ui->comboBox_tp->model()->index(ui->comboBox_tp->currentIndex(),1).data().toString();
    }
    else
        return ui->comboBox_xp->itemData(ui->comboBox_xp->currentIndex()).toString();
}
//
QList<QStandardItem *> Dangkyphieutiem::prepareRow(const QString &first,
                                                const QString &second,
                                                const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}


void Dangkyphieutiem::on_pushButton_2_clicked()
{
    /*xoa ben danh sach chon*/
    itemModel.removeRow(ui->listView_duocchon->currentIndex().row());
}

void Dangkyphieutiem::on_listView_benh_doubleClicked(const QModelIndex &index)
{
    mot = this->list_benh->index(index.row(),0).data().toString();
    hai = this->list_benh->index(index.row(),1).data().toString();
    ba = "";
    itemModel.appendRow(this->prepareRow(mot,hai,ba));
}

void Dangkyphieutiem::on_pushButton_3_clicked()
{
    qDebug() << id.getNextIndexCode("tt_benh_nhan","BN");
}
void Dangkyphieutiem::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return)
       qDebug()<< "enter";
}


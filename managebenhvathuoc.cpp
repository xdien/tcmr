#include "managebenhvathuoc.h"
#include "ui_managebenhvathuoc.h"

managebenhvathuoc::managebenhvathuoc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::managebenhvathuoc)
{
    ui->setupUi(this);

    tkFocus = false;

    dsbenhmodel.setQuery("SELECT ma_benh, ten_benh, la_vx "
                         "FROM benh");
    ui->tableView_dsbenh->hideColumn(0);
    ui->tableView_dsbenh->setModel(&dsbenhmodel);
    //dsbenhmodel.setHeaderData(0,Qt::Horizontal,"Mã Thuốc");

    dsthuocmodel.setQuery("select distinct thuoc.ma_thuoc, ten_thuoc, vung_tiem, dung_tich, gia_ap_dung from thuoc left join don_gia on don_gia.ma_thuoc = thuoc.ma_thuoc");
    ui->tableView_dsthuoc->setModel(&dsthuocmodel);
    ui->tableView_dsthuoc->hideColumn(0);


    //benhdcchonmodel = new QSqlRelationalTableModel;
    ui->treeView_benhdcchon->setModel(&benhdcchonmodel);


    //benhdcchonmodel.setTable("phong_ngua");
    //benhdcchonmodel.setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->comboBox_2->setModel(&dotuoimodel);
    dotuoimodel.setQuery("SELECT do_tuoi, ma_dotuoi "
                         "FROM do_tuoi");
    contextMenu = new QMenu();
    ui->treeView_benhdcchon->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView_dsbenh->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView_dsthuoc->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeView_benhdcchon,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onCustomContextMenu(QPoint)));
    connect(ui->tableView_dsbenh,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onCustomContextMenu_benh(QPoint)));
    connect(ui->tableView_dsthuoc,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onCustomContextMenu_thuoc(QPoint)));

    ui->lineEdit->setText("Nhập bệnh mới...");
    ui->lineEdit_tkthuoc->setText("Nhập thuốc cần tìm...");
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_tkthuoc->installEventFilter(this);
    /*repx*/
    QRegExp sdt_rx("\\d{1,8}");
    QValidator *validator_sdt = new QRegExpValidator(sdt_rx, this);
    ui->lineEdit_capnhatgia->setValidator(validator_sdt);

    dsbenhmodel.setHeaderData(0,Qt::Horizontal,QString::fromUtf8("Mã bệnh"));
    dsbenhmodel.setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Tên bệnh"));
    dsbenhmodel.setHeaderData(2,Qt::Horizontal,QString::fromUtf8("là thuốc"));

    dsthuocmodel.setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Tên thuốc"));
    dsthuocmodel.setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Vùng tiêm"));
    dsthuocmodel.setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Dung tích"));
    dsthuocmodel.setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Giá áp dụng"));

    ui->tableView->setModel(&itemLichhen);
    tuTang = 0;
}
managebenhvathuoc::~managebenhvathuoc()
{
    delete ui;
    delete contextMenu;
}

void managebenhvathuoc::on_tableView_dsbenh_clicked(const QModelIndex &index)
{
    //this->dsbenhmodel.index(index.row(),0).data();
    maBn = this->dsbenhmodel.index(index.row(),0).data().toString();
    benhdcchonmodel.setQuery("select * from phong_ngua where ma_benh = '"+ maBn +"'");
    mabenh = maBn;

}


//add item model
QList<QStandardItem *> managebenhvathuoc::prepareRow(const QString &first,
                                                const QString &second,
                                                const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}

void managebenhvathuoc::on_lineEdit_returnPressed()
{
    if(ui->checkBox->isChecked())
        lavx = "TRUE";
    else
        lavx = "FALSE";
    maBn = id.getNextIndexCode("benh","BH");
    query.exec("INSERT INTO benh("
               "ma_benh, ten_benh, la_vx)"
               "VALUES ('"+maBn+"', '"+ui->lineEdit->text()+"', '"+lavx+"')");
    dsbenhmodel.setQuery("SELECT ma_benh, ten_benh, la_vx "
                         "FROM benh");
}

void managebenhvathuoc::on_pushButton_themdotuoi_clicked()
{
    dotuoi = ui->spinBox->text() + " - " + ui->spinBox_2->text() + " " + ui->comboBox_thangnam->currentText();
    maBn = id.getNextIndexCode("do_tuoi","DT");
    query.exec("select do_tuoi from do_tuoi where do_tuoi = '"+dotuoi+"'");
    if(!query.next())
    {
    if(query.exec("INSERT INTO do_tuoi("
               "ma_dotuoi, do_tuoi, dvt, tu, den) "
               "VALUES ('"+maBn+"', '"+dotuoi+"', '"+ui->comboBox_thangnam->currentText()+"', '"+ui->spinBox->text()+"', '"+ui->spinBox_2->text()+"')"))
        qDebug()<<query.lastError().text();
    dotuoimodel.setQuery("SELECT do_tuoi, ma_dotuoi "
                         "FROM do_tuoi");
    }
}

void managebenhvathuoc::on_pushButton_themthuoc_clicked()
{
    maBn = id.getNextIndexCode("thuoc","TH");
    maLh = id.getNextIndexCode("lich_hen","LH");
    dotuoi = dotuoimodel.index(ui->comboBox_2->currentIndex(),1).data().toString();
    if(!query.exec("INSERT INTO thuoc("
               "ma_thuoc, ma_dotuoi, ten_thuoc, vung_tiem, dung_tich, lieu_dung) "
               "VALUES ('"+maBn+"', '"+dotuoi+"', '"+ui->lineEdit_tenthuoc->text()+"', '"+ui->comboBox_vungtiem->currentText()+"', '"+ui->lineEdit_dungtich->text()+"', '"+ui->lineEdit_lieudung->text()+"')"))
        qDebug()<<query.lastError().text();
    else
    {
        query.exec("insert into don_gia(ma_thuoc, gia, ngay, gia_ap_dung) values('"+maBn+"', '"+ui->lineEdit_gia->text()+"', current_date,'"+ui->lineEdit_gia->text()+"')");
        dsthuocmodel.setQuery("select distinct thuoc.ma_thuoc, ten_thuoc, vung_tiem, dung_tich, gia_ap_dung from thuoc left join don_gia on don_gia.ma_thuoc = thuoc.ma_thuoc");

        for(int i=0;i<=itemLichhen.rowCount();i++)
        {
            if(!query.exec("INSERT INTO lich_hen( "
                       "ma_thuoc, ma_lich_hen, lan_thu, so_ngay) "
                       "VALUES ('"+maBn+"', '"+maLh+"', '"+QString::number(i+1)+"', '"+itemLichhen.index(i,1).data().toString()+"')"))
                qDebug() << query.lastError().text();
            qDebug() << i;
        }

        tuTang = 0;
        ui->comboBox_2->setCurrentIndex(-1);
        ui->lineEdit_tenthuoc->clear();
        ui->comboBox_vungtiem->setCurrentIndex(-1);
        ui->lineEdit_dungtich->clear();
        ui->lineEdit_gia->clear();
        ui->lineEdit_lieudung->clear();
        itemLichhen.clear();
        ui->label_12->setText("Số ngày của lần tiêm thứ 1:");
    }
}

void managebenhvathuoc::on_tableView_dsthuoc_doubleClicked(const QModelIndex &index)
{
    //kiem tra kq truy van
    if(query.exec("INSERT INTO phong_ngua("
               "ma_benh, ma_thuoc) "
               "VALUES ('"+mabenh+"', '"+this->dsthuocmodel.index(index.row(),0).data().toString()+"')"))
        qDebug() << query.lastError().text();
    benhdcchonmodel.setQuery("select * from phong_ngua where ma_benh = '"+ mabenh +"'");

}
void managebenhvathuoc::onCustomContextMenu(const QPoint &point){
    index = ui->treeView_benhdcchon->indexAt(point);
    if (index.isValid()) {
        mabenh = benhdcchonmodel.index(index.row(),0).data().toString();
        mathuoc = benhdcchonmodel.index(index.row(),1).data().toString();
        QAction action1("Xóa", this);
        connect(&action1, SIGNAL(triggered()), this, SLOT(xoathuocthuocbenh()));
        contextMenu->addAction(&action1);
        contextMenu->exec(ui->treeView_benhdcchon->mapToGlobal(point));
    }
}
void managebenhvathuoc::onCustomContextMenu_benh(const QPoint &point){
    index = ui->tableView_dsbenh->indexAt(point);
    if (index.isValid()) {
        mabenh = benhdcchonmodel.index(index.row(),0).data().toString();
        mathuoc = benhdcchonmodel.index(index.row(),1).data().toString();
        QAction action1("Xóa", this);
        connect(&action1, SIGNAL(triggered()), this, SLOT(xoa_benh()));
        contextMenu->addAction(&action1);
        contextMenu->exec(ui->tableView_dsbenh->mapToGlobal(point));
    }
}
void managebenhvathuoc::onCustomContextMenu_thuoc(const QPoint &point){
    index = ui->tableView_dsthuoc->indexAt(point);
    if (index.isValid()) {
        mabenh = benhdcchonmodel.index(index.row(),0).data().toString();
        mathuoc = benhdcchonmodel.index(index.row(),1).data().toString();
        QAction action1("Xóa", this);
        connect(&action1, SIGNAL(triggered()), this, SLOT(xoa_thuoc()));
        contextMenu->addAction(&action1);
        contextMenu->exec(ui->tableView_dsthuoc->mapToGlobal(point));
    }
}
void managebenhvathuoc::xoathuocthuocbenh()
{
    query.exec("DELETE FROM phong_ngua "
               "WHERE ma_benh = '"+mabenh+"' and ma_thuoc = '"+mathuoc+"'");
    benhdcchonmodel.setQuery("select * from phong_ngua where ma_benh = '"+ mabenh +"'");

}

bool managebenhvathuoc::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::FocusIn)
    {
        if(obj->objectName()=="lineEdit")
        {
            if(ui->lineEdit->text()=="Nhập bệnh mới...")
                ui->lineEdit->setText("");
        }
        else
        {
            if(ui->lineEdit_tkthuoc->text()=="Nhập thuốc cần tìm...")
            {
                tkFocus = true;
                ui->lineEdit_tkthuoc->setText("");
            }
        }
    }
    else if(event->type() == QEvent::FocusOut)
    {
        if(obj->objectName()=="lineEdit")
        {
            if(ui->lineEdit->text()=="")
               ui->lineEdit->setText("Nhập bệnh mới...");
        }
        else
        {
            if(ui->lineEdit_tkthuoc->text()=="")
            {
               ui->lineEdit_tkthuoc->setText("Nhập thuốc cần tìm...");
               dsthuocmodel.setQuery("select distinct thuoc.ma_thuoc, ten_thuoc, vung_tiem, dung_tich, gia_ap_dung from thuoc left join don_gia on don_gia.ma_thuoc = thuoc.ma_thuoc");

            }
        }
    }
    return false;
}

void managebenhvathuoc::on_lineEdit_tkthuoc_textChanged(const QString &arg1)
{
    if(tkFocus)
        dsthuocmodel.setQuery("select distinct thuoc.ma_thuoc, ten_thuoc, vung_tiem, dung_tich, gia_ap_dung from thuoc left join don_gia on don_gia.ma_thuoc = thuoc.ma_thuoc where ten_thuoc ilike '%"+ui->lineEdit_tkthuoc->text()+"%'");
}
void managebenhvathuoc::xoa_benh()
{
    query.exec("DELETE FROM benh "
               "WHERE ma_benh = '"+dsbenhmodel.index(ui->tableView_dsbenh->currentIndex().row(),0).data().toString()+"'");
    dsbenhmodel.setQuery("SELECT ma_benh, ten_benh, la_vx "
                         "FROM benh");
}
void managebenhvathuoc::xoa_thuoc()
{
    query.exec("DELETE FROM thuoc "
               "WHERE ma_thuoc = '"+dsthuocmodel.index(ui->tableView_dsthuoc->currentIndex().row(),0).data().toString()+"'");
    dsthuocmodel.setQuery("select distinct thuoc.ma_thuoc, ten_thuoc, vung_tiem, dung_tich, gia_ap_dung from thuoc left join don_gia on don_gia.ma_thuoc = thuoc.ma_thuoc");

}

void managebenhvathuoc::on_pushButton_capnhatgia_clicked()
{
    if(!query.exec("insert into don_gia(ma_thuoc, ngay, gia) values('"+dsthuocmodel.index(ui->tableView_dsthuoc->currentIndex().row(),0).data().toString()+"', current_date , '"+ui->lineEdit_capnhatgia->text()+"')"))
    qDebug()<<query.lastError().text();
    else
    {
        query.exec("update don_gia set gia_ap_dung='"+ui->lineEdit_capnhatgia->text()+"' where ma_thuoc='"+dsthuocmodel.index(ui->tableView_dsthuoc->currentIndex().row(),0).data().toString()+"'");
        dsthuocmodel.setQuery("select distinct thuoc.ma_thuoc, ten_thuoc, vung_tiem, dung_tich, gia_ap_dung from thuoc left join don_gia on don_gia.ma_thuoc = thuoc.ma_thuoc");
        ui->lineEdit_capnhatgia->clear();
    }
}

void managebenhvathuoc::on_lineEdit_2_returnPressed()
{
    tuTang=tuTang+1;
    itemLichhen.appendRow(this->prepareRow(QString::number(tuTang),ui->lineEdit_2->text(),""));
    ui->label_12->setText("Số ngày của lần tiêm thứ "+QString::number(tuTang+1)+":");
    ui->lineEdit_2->setText("");
}


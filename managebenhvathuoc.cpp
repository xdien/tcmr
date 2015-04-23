#include "managebenhvathuoc.h"
#include "ui_managebenhvathuoc.h"

managebenhvathuoc::managebenhvathuoc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::managebenhvathuoc)
{
    ui->setupUi(this);

    dsbenhmodel.setQuery("SELECT ma_benh, ten_benh, la_vx "
                         "FROM benh");
    ui->tableView_dsbenh->hideColumn(0);
    ui->tableView_dsbenh->setModel(&dsbenhmodel);
    //dsbenhmodel.setHeaderData(0,Qt::Horizontal,"Mã Thuốc");

    dsthuocmodel.setQuery("select ma_thuoc, ten_thuoc, vung_tiem, dung_tich from thuoc");
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
    connect(ui->treeView_benhdcchon,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onCustomContextMenu(QPoint)));

    ui->lineEdit->setText("Nhập bệnh mới...");
    ui->lineEdit_tkthuoc->setText("Nhập thuốc cần tìm...");
}

managebenhvathuoc::~managebenhvathuoc()
{
    delete ui;
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
    maBn = id.getNextIndexCode("benh","BN");
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
    query.exec("INSERT INTO do_tuoi("
               "ma_dotuoi, do_tuoi, lieu_dung, dvt, tu, den) "
               "VALUES ('"+maBn+"', '"+dotuoi+"', '"+ui->lineEdit_lieudung->text()+"', '"+ui->comboBox_thangnam->currentText()+"', '"+ui->spinBox->text()+"', '"+ui->spinBox_2->text()+"')");
    dotuoimodel.setQuery("SELECT do_tuoi, ma_dotuoi "
                         "FROM do_tuoi");
}

void managebenhvathuoc::on_pushButton_themthuoc_clicked()
{
    maBn = id.getNextIndexCode("thuoc","TH");
    dotuoi = dotuoimodel.index(ui->comboBox_2->currentIndex(),1).data().toString();
    query.exec("INSERT INTO thuoc("
               "ma_thuoc, ma_dotuoi, ten_thuoc, vung_tiem, dung_tich) "
               "VALUES ('"+maBn+"', '"+dotuoi+"', '"+ui->lineEdit_tenthuoc->text()+"', '"+ui->comboBox_vungtiem->currentText()+"', '"+ui->lineEdit_dungtich->text()+"')");
    dsthuocmodel.setQuery("select ten_thuoc, vung_tiem, dung_tich from thuoc");

}

void managebenhvathuoc::on_tableView_dsthuoc_doubleClicked(const QModelIndex &index)
{
    query.exec("INSERT INTO phong_ngua("
               "ma_benh, ma_thuoc) "
               "VALUES ('"+mabenh+"', '"+this->dsthuocmodel.index(index.row(),0).data().toString()+"')");
    benhdcchonmodel.setQuery("select * from phong_ngua where ma_benh = '"+ mabenh +"'");

}
void managebenhvathuoc::onCustomContextMenu(const QPoint &point){
    index = ui->treeView_benhdcchon->indexAt(point);
    if (index.isValid()) {
        mabenh = benhdcchonmodel.index(index.row(),0).data().toString();
        mathuoc = benhdcchonmodel.index(index.row(),1).data().toString();
        QAction action1("Remove Data Point", this);
        connect(&action1, SIGNAL(triggered()), this, SLOT(xoathuocthuocbenh()));
        contextMenu->addAction(&action1);
        contextMenu->exec(ui->treeView_benhdcchon->mapToGlobal(point));
    }
}
void managebenhvathuoc::xoathuocthuocbenh()
{
    query.exec("DELETE FROM phong_ngua "
               "WHERE ma_benh = '"+mabenh+"' and ma_thuoc = '"+mathuoc+"'");
    benhdcchonmodel.setQuery("select * from phong_ngua where ma_benh = '"+ mabenh +"'");

}

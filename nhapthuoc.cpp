#include "nhapthuoc.h"
#include "ui_nhapthuoc.h"

NhapThuoc::NhapThuoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NhapThuoc)
{
    ui->setupUi(this);
    table_thuoc = new QSqlRelationalTableModel();
    table_dotuoi.setEditStrategy(QSqlTableModel::OnRowChange);
    sqlde = new QSqlRelationalDelegate();
    //khoi dong bang do tuoi
    this->loadTableDoTuoi();
    this->loadTableThuoc();
    ui->tableView_thuoc->hideColumn(0);
}

NhapThuoc::~NhapThuoc()
{
    delete ui;
}

void NhapThuoc::loadTableDoTuoi()
{
    table_dotuoi.setTable("do_tuoi");
    ui->tableView_dotuoi->setModel(&table_dotuoi);
    table_dotuoi.select();
}
void NhapThuoc::loadTableThuoc()
{
    table_thuoc->setTable("thuoc");
    ui->tableView_thuoc->setModel(table_thuoc);
    table_thuoc->select();
    table_thuoc->setRelation(1,QSqlRelation("do_tuoi","ma_dotuoi","do_tuoi"));
    ui->tableView_thuoc->setItemDelegate(sqlde);
}

void NhapThuoc::insertRow(QSqlTableModel &table_mode)
{
    rowCount = table_mode.rowCount();
    if(!table_mode.insertRow(rowCount))
    {

        qDebug()<<"Inserows for recoder table: "<<table_mode.lastError().text();
    }
    else
    {
        ma_dt = id.getNextIndexCode("do_tuoi","DT");
        table_mode.setData(table_mode.index(rowCount,0),ma_dt);
        ui->tableView_dotuoi->selectRow(rowCount);
    }
}
void NhapThuoc::insertRow(QSqlRelationalTableModel *table_mode)
{
    rowCount = table_mode->rowCount();
    if(!table_mode->insertRow(rowCount))
    {

        qDebug()<<"Inserows for recoder table: "<<table_mode->lastError().text();
    }
    else
    {
        ma_thuoc = id.getNextIndexCode("thuoc","TH");
        table_mode->setData(table_mode->index(rowCount,0),ma_thuoc);
        ui->tableView_thuoc->selectRow(rowCount);
    }
}


void NhapThuoc::on_pushButton_2_clicked()
{
    this->insertRow(table_dotuoi);
}

void NhapThuoc::on_pushButton_3_clicked()
{
    if(table_dotuoi.submitAll())
    {
        this->loadTableThuoc();
    }else{
        qDebug() << table_dotuoi.lastError().text();
    }
}

void NhapThuoc::on_pushButton_themthuoc_clicked()
{
    this->insertRow(table_thuoc);
}

void NhapThuoc::on_pushButton_luuthuoc_clicked()
{
    if(table_thuoc->submitAll()){

    }else{
        qDebug() << table_thuoc->lastError().text();
    }
}

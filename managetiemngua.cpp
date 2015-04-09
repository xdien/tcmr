#include "managetiemngua.h"
#include "ui_managetiemngua.h"

#include <QKeyEvent>

ManageTiemNgua::ManageTiemNgua(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageTiemNgua)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("qt_sql_default_connection");

    danhsachbenh.setTable("benh");
    ui->tableView_benh->setModel(&danhsachbenh);
    danhsachbenh.select();
    //hien thi phong ngua
    phong_ngua.setTable("phong_ngua");
    phong_ngua.setRelation(0,QSqlRelation("benh","ma_benh","ten_benh"));
    phong_ngua.setRelation(1,QSqlRelation("thuoc","ma_thuoc","ten_thuoc"));
    phong_ngua.setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_phong->setModel(&phong_ngua);

    phong_ngua.select();
    ui->tableView_phong->setItemDelegate(new QSqlRelationalDelegate);
    ui->tableView_benh->hideColumn(0);
}

ManageTiemNgua::~ManageTiemNgua()
{
    delete ui;
}

void ManageTiemNgua::on_pushButton_clicked()
{
    danhsachbenh.submitAll();
    this->up_bang_phongNgua();
}

void ManageTiemNgua::up_bang_phongNgua()
{
    phong_ngua.setTable("phong_ngua");
    phong_ngua.setRelation(0,QSqlRelation("benh","ma_benh","ten_benh"));
    phong_ngua.setRelation(1,QSqlRelation("thuoc","ma_thuoc","ten_thuoc"));
    phong_ngua.setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_phong->setModel(&phong_ngua);
    phong_ngua.select();
    ui->tableView_phong->setItemDelegate(new QSqlRelationalDelegate);
}
void ManageTiemNgua::insertRow()
{
    int rowCount;
    rowCount = phong_ngua.rowCount();
    if(!phong_ngua.insertRow(rowCount))
    {

        qDebug()<<"Inserows for recoder table: "<<phong_ngua.lastError().text();
    }
    else
    {
        //ma_nv = id.getNextIndexCode("nhan_vien","NV");
        phong_ngua.setData(phong_ngua.index(rowCount,0),ma_benh);
        phong_ngua.fetchMore();
        ui->tableView_phong->selectRow(rowCount);
    }
}

void ManageTiemNgua::keyPressEvent(QKeyEvent *e)
{
    if(e->matches(QKeySequence::Italic))
    {

        rowCount = danhsachbenh.rowCount();
        if(!danhsachbenh.insertRow(rowCount))
        {

            qDebug()<<"Inserows for recoder table: "<<danhsachbenh.lastError().text();
        }
        else
        {
            ma_benh = id.getNextIndexCode("benh","BH");
            danhsachbenh.setData(danhsachbenh.index(rowCount,0),ma_benh);
            ui->tableView_benh->selectRow(rowCount);
        }
    }
    if(e->matches(QKeySequence::Bold))
    {
        rowCount = phong_ngua.rowCount();
        if(!phong_ngua.insertRow(rowCount))
        {

            qDebug()<<"Inserows for recoder table: "<<phong_ngua.lastError().text();
        }
        else
        {
//            ma_benh = id.getNextIndexCode("benh","BH");
//            phong_ngua.setData(phong_ngua.index(rowCount,0),ma_benh);
            ui->tableView_phong->selectRow(rowCount);
        }
    }
}

void ManageTiemNgua::on_pushButton_2_clicked()
{
    if(!phong_ngua.submitAll())
        qDebug() << "KHong the cap nhat bang phong ngua: " << phong_ngua.lastError().text();
}

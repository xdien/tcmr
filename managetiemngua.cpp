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
//    ma_benh = id.getNextIndexCode("benh","BH");
//    if(ui->checkBox->isChecked())
//    {
//        if(query.exec("INSERT INTO benh(ma_benh, ten_benh, la_vx) VALUES ('"+ma_benh+"', '"+ui->lineEdit->text()+"', FALSE);"))
//            qDebug() << "Khong the them benh: " << query.lastError().text();
//    }else{
//        if(query.exec("INSERT INTO benh(ma_benh, ten_benh, la_vx) VALUES ('"+ma_benh+"', '"+ui->lineEdit->text()+"', TRUE);"))
//            qDebug() << "Khong the them benh: " << query.lastError().text();
//    }
//    danhsachbenh.select();
//    this->insertRow();
    danhsachbenh.submitAll();
    this->up_bang_phongNgua();
}

void ManageTiemNgua::on_tableView_phong_pressed(const QModelIndex &index)
{

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
        int rowCount;
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
}

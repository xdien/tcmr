#include "managechucvu.h"
#include "ui_managechucvu.h"

#include <QMenu>

ManageChucVu::ManageChucVu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageChucVu)
{
    ui->setupUi(this);
    tablemodel = new QSqlTableModel();
    tablemodel->setTable("chuc_vu");
    tablemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_cv->setModel(tablemodel);
    tablemodel->select();
    //set chuc vu;
    chuc_vu = new QSqlRelationalTableModel();
    chuc_vu->setTable("phan_quyen");
    chuc_vu->setEditStrategy(QSqlTableModel::OnManualSubmit);
    chuc_vu->setRelation(0,QSqlRelation("chuc_vu","ma_cv","ten_cv"));
    chuc_vu->select();
    ui->tableView->setModel(chuc_vu);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate);
}

ManageChucVu::~ManageChucVu()
{
    delete ui;
}

void ManageChucVu::keyPressEvent(QKeyEvent *e)
{
    int rowCount;
    if(e->matches(QKeySequence::Italic))
    {
        rowCount = chuc_vu->rowCount();
        if(!chuc_vu->insertRow(rowCount))
        {

            qDebug()<<"Inserows for recoder table: "<<chuc_vu->lastError().text();
        }
        else
        {
            //ma_nv = id.getNextIndexCode("nhan_vien","NV");
            //tablemodel->setData(testmodel->index(rowCount,0),ma_nv);
            ui->tableView->selectRow(rowCount);
        }
    }
    if(e->matches(QKeySequence::Bold))
    {
        rowCount = tablemodel->rowCount();
        if(!tablemodel->insertRow(rowCount))
        {

            qDebug()<<"Inserows for recoder table: "<<tablemodel->lastError().text();
        }
        else
        {
            ma_cv = id.getNextIndexCode("chuc_vu","NV");
            tablemodel->setData(tablemodel->index(rowCount,0),ma_cv);
            ui->tableView_cv->selectRow(rowCount);
        }
    }
}

void ManageChucVu::on_pushButton_clicked()
{
    if(chuc_vu->submitAll())
        qDebug() << "loi submit" << chuc_vu->lastError().text();
    if(tablemodel->submitAll())
        qDebug() << "loi submit phan_quyen: "<< tablemodel->lastError().text();
    this->update_phanquyen();
}
void ManageChucVu::update_phanquyen()
{
    chuc_vu->setRelation(0,QSqlRelation("chuc_vu","ma_cv","ten_cv"));
    chuc_vu->select();
    ui->tableView->setModel(chuc_vu);
    //ui->tableView->setItemDelegate(new QSqlRelationalDelegate);
}



void ManageChucVu::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    //menu = new QMenu();
    menu.addAction("Menu Item 1");
    menu.exec(pos);
    qDebug() << "Customenu";
}

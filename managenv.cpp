#include "managenv.h"
#include "ui_managenv.h"
#include <QSqlRelationalDelegate>

ManageNV::ManageNV(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageNV)
{
    ui->setupUi(this);
    QSqlRelation rela;
    testmodel = new QSqlRelationalTableModel();
   testmodel->setTable("nhan_vien");

    testmodel->setRelation(1,QSqlRelation("chuc_vu","ma_cv","ten_cv"));
    testmodel->select();
    ui->tableView->setModel(testmodel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate());
}

ManageNV::~ManageNV()
{
    delete ui;
}

void ManageNV::on_pushButton_clicked()
{

}

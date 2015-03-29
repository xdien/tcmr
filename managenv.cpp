#include "managenv.h"
#include "ui_managenv.h"
#include <QSqlRelationalDelegate>

ManageNV::ManageNV(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageNV)
{
    ui->setupUi(this);
    testmodel = new QSqlRelationalTableModel();
    testmodel->setTable("nhan_vien");
    testmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //testmodel->set;
    testmodel->setRelation(1,QSqlRelation("chuc_vu","ma_cv","ten_cv"));
    testmodel->select();
    ui->tableView->setModel(testmodel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate());
    ui->tableView->hideColumn(0);
}

ManageNV::~ManageNV()
{
    delete ui;
}

void ManageNV::on_pushButton_clicked()
{
    //ui->tableView->
    row = ui->tableView->currentIndex().row();
    if(!testmodel->submitAll())
    {
        qDebug() << "Loi khong the luu: " << testmodel->lastError().text();
    }
}

void ManageNV::keyPressEvent(QKeyEvent *e)
{
    if(e->matches(QKeySequence::Italic))
    {
        int rowCount;
         rowCount = testmodel->rowCount();
         if(!testmodel->insertRow(rowCount))
         {

             qDebug()<<"Inserows for recoder table: "<<testmodel->lastError().text();
         }
         else
         {
             ma_nv = id.getNextIndexCode("nhan_vien","NV");
              testmodel->setData(testmodel->index(rowCount,0),ma_nv);
             ui->tableView->selectRow(rowCount);
         }
    }
}
QList<QStandardItem *> ManageNV::prepareRow(const QString &first,
                                                const QString &second,
                                                const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}

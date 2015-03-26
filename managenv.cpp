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
//    qDebug() << testmodel->index(row,2).data().toString();
//    testmodel->setData(model_idx,"dsadasd");
//    chuc_vu = testmodel->index(row,1).sibling(0,0).data().toString();
//    ten = testmodel->index(row,2).data().toString();
//    mk = testmodel->index(row,3).data().toString();
//    ten_dn = testmodel->index(row,4).data().toString();
//    sdt = testmodel->index(row,5).data().toString();
//    cmnd = testmodel->index(row,6).data().toString();
//    que_quan = testmodel->index(row,7).data().toString();
//    //testmodel->insertRows()
//    query.exec("INSERT INTO nhan_vien(\
//               ma_nv, ma_cv, ten_nv, mat_khau, ten_dn, sdt, cmnd, que_quan)\
//            VALUES ('"+ma_nv+"', '"+chuc_vu+"', '"+ten+"', '"+mk+"', '"+ten_dn+"', '"+sdt+"', '"+cmnd+"', '"+que_quan+"')");
//            qDebug() << query.lastError().text();
//    testmodel->select();
    testmodel->submitAll();
    //testmodel->setItemData(QModelIndex(1,1))
    //testmodel->submitAll();
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

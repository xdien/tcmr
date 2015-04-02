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
    //load phan quyen
        chuc_vumodel = new QSqlRelationalTableModel();
        dele = new QSqlRelationalDelegate();
        this->LoadtableQuyen();
    //testmodel->set;
    testmodel->setRelation(1,QSqlRelation("chuc_vu","ma_cv","ten_cv"));
    testmodel->select();
    ui->tableView->setModel(testmodel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate());
    ui->tableView->hideColumn(0);
    this->LoadChucvu();
    //khong cho phep click
    ui->checkBox_1h->setEnabled(false);
    ui->checkBox_2h->setEnabled(false);
    ui->checkBox_3h->setEnabled(false);
    ui->checkBox_4h->setEnabled(false);
    ui->checkBox_5h->setEnabled(false);
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

void ManageNV::LoadCheckbox(QString macv, QCheckBox *c1, QCheckBox *c2, QCheckBox *c3, QCheckBox *c4, QCheckBox *c5)
{
    c1->setChecked(false);
    c2->setChecked(false);
    c3->setChecked(false);
    c4->setChecked(false);
    c5->setChecked(false);
    query.exec("select * from phan_quyen where ma_cv = '" +macv+ "'");
    if(query.next())
    {
        c1->setChecked(query.value(1).toBool());
        c2->setChecked(query.value(2).toBool());
        c3->setChecked(query.value(3).toBool());
        c4->setChecked(query.value(4).toBool());
        c5->setChecked(query.value(5).toBool());
    }
}

//ham load du lieu chuc vu
void ManageNV::LoadChucvu()
{
    this->chucVuModel.setQuery("select ten_cv,ma_cv from chuc_vu");
    ui->comboBox_chucVu->setModel(&chucVuModel);
}

void ManageNV::on_comboBox_chucVu_currentIndexChanged(int index)
{
    this->LoadCheckbox(chucVuModel.index(index,1).data().toString(),ui->checkBox_1h,ui->checkBox_2h,ui->checkBox_3h,ui->checkBox_4h,ui->checkBox_5h);
}

void ManageNV::LoadtableQuyen()
{
    chuc_vumodel->setTable("phan_quyen");
    chuc_vumodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //chuc_vumodel->setRelation(0,QSqlRelation("chuc_vu","ma_cv","ten_cv"));
    chuc_vumodel->select();
    ui->tableView_phanquyen->setModel(chuc_vumodel);
    //ui->tableView_phanquyen->hideColumn(0);
    ui->tableView_phanquyen->setItemDelegate(new QSqlRelationalDelegate);
}

void ManageNV::on_pushButton_4_clicked()
{
    if(!this->chuc_vumodel->submitAll())
    {
        chuc_vumodel->relationModel(0);
        qDebug() << "Loi submit: " << chuc_vumodel->lastError().text();
    }
    else
    this->on_comboBox_chucVu_currentIndexChanged(ui->comboBox_chucVu->currentIndex());
}

void ManageNV::on_pushButton_2_clicked()
{
    this->LoadChucvu();
    //them thong tien chuc vu va quyen cua chuc vu do


}

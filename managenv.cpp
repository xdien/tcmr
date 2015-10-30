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
    contextMenu =new QMenu();
    //contextMenu->acceptDrops()
    //load phan quyen
    chuc_vumodel = new QSqlRelationalTableModel();
    dele = new QSqlRelationalDelegate();
    this->LoadtableQuyen();
    //testmodel->set;

    testmodel->setRelation(1,QSqlRelation("chuc_vu","ma_cv","ten_cv"));
    chuc_vumodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    testmodel->select();
    /*-----------------*/
    //testmodel->set

    ui->tableView->setModel(testmodel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate());
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(3);
    //dat ten cho cac cot trong bang
    testmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Chức vụ"));
    testmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Họ tên"));
    testmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Tên DN"));
    testmodel->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("SĐT"));
    testmodel->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("CMND"));
    testmodel->setHeaderData(7,Qt::Horizontal,QString::fromUtf8("Quê Quán"));
    //tao su kien right click cho bang
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
    this->LoadChucvu();
    //khong cho phep click
    ui->checkBox_1h->setEnabled(false);
    ui->checkBox_2h->setEnabled(false);
    ui->checkBox_3h->setEnabled(false);
    ui->checkBox_4h->setEnabled(false);
    ui->checkBox_5h->setEnabled(false);
    ui->checkBox_6h->setEnabled(false);
    /*bat buoc dung kieu so cho line_edit cmnd va sdt*/
    QRegExp rx("\\d{1,9}");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->lineEdit_cmnd->setValidator(validator);
    //sdt
    QRegExp sdt_rx("[0][1,9][0,1,2,3,4,6,7.9]\\d{1,8}");
    QValidator *validator_sdt = new QRegExpValidator(sdt_rx, this);
    ui->lineEdit_sdt->setValidator(validator_sdt);
}

ManageNV::~ManageNV()
{
    delete ui;
    delete contextMenu;
    delete testmodel;
    delete dele;
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

void ManageNV::LoadCheckbox(QString macv, QCheckBox *c1, QCheckBox *c2, QCheckBox *c3, QCheckBox *c4, QCheckBox *c5, QCheckBox *c6)
{
    c1->setChecked(false);
    c2->setChecked(false);
    c3->setChecked(false);
    c4->setChecked(false);
    c5->setChecked(false);
    c6->setChecked(false);
    query.exec("select * from chuc_vu where ma_cv = '" +macv+ "'");
    if(query.next())
    {
        c1->setChecked(query.value(2).toBool());
        c2->setChecked(query.value(3).toBool());
        c3->setChecked(query.value(4).toBool());
        c4->setChecked(query.value(5).toBool());
        c5->setChecked(query.value(6).toBool());
        c6->setChecked(query.value(7).toBool());
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
    this->LoadCheckbox(chucVuModel.index(index,1).data().toString(),ui->checkBox_1h,ui->checkBox_2h,ui->checkBox_3h,ui->checkBox_4h,ui->checkBox_5h,ui->checkBox_6h);
}

void ManageNV::LoadtableQuyen()
{
//    chuc_vumodel->setTable("phan_quyen");
//    chuc_vumodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    chuc_vumodel->setRelation(0,QSqlRelation("chuc_vu","ma_cv","ten_cv"));
//    chuc_vumodel->select();
//    ui->tableView_phanquyen->setModel(chuc_vumodel);
//    //ui->tableView_phanquyen->hideColumn(0);
//    ui->tableView_phanquyen->setItemDelegate(new QSqlRelationalDelegate);
    //phanquyenModel.setQuery("select * from chuc_vu");
    phanquyenModel.setTable("chuc_vu");
    phanquyenModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    phanquyenModel.select();
    ui->tableView_phanquyen->setModel(&phanquyenModel);
    ui->tableView_phanquyen->hideColumn(0);

    ui->tableView_phanquyen->setItemDelegate(new QSqlRelationalDelegate);
    phanquyenModel.setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Tên nhân viên"));
    phanquyenModel.setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Đăng ký TT"));
    phanquyenModel.setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Khám sơ bộ"));
    phanquyenModel.setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Đóng phí"));
    phanquyenModel.setHeaderData(5,Qt::Horizontal,QString::fromUtf8("Tiêm"));
    phanquyenModel.setHeaderData(6,Qt::Horizontal,QString::fromUtf8("Báo cáo"));
    phanquyenModel.setHeaderData(7,Qt::Horizontal,QString::fromUtf8("Hệ thống"));
}

void ManageNV::on_pushButton_4_clicked()
{
    if(!this->phanquyenModel.submitAll())
    {
        //phanquyenModel->relationModel(0);
        qDebug() << "Loi submit: " << phanquyenModel.lastError().text();
    }
    else
    this->on_comboBox_chucVu_currentIndexChanged(ui->comboBox_chucVu->currentIndex());
}

void ManageNV::on_pushButton_2_clicked()
{

    ma_cv = id.getNextIndexCode("chuc_vu","CV");
    query.exec("INSERT INTO chuc_vu(\
               ma_cv, ten_cv, dang_ky_tt, kham_so_bo, dong_phi, tiem, bao_cao, he_thong)\
       VALUES ('"+ma_cv+"', '"+ui->lineEdit_tencv->text()+"',"+boolToString(ui->checkBox_1->isChecked())+", "+boolToString(ui->checkBox_2->isChecked())+", "+boolToString(ui->checkBox_3->isChecked())+", "+boolToString(ui->checkBox_4->isChecked())+","+boolToString(ui->checkBox_5->isChecked())+", "+boolToString(ui->checkBox_6->isChecked())+")");
    qDebug() << query.lastError().text();
    this->LoadChucvu();
    this->LoadtableQuyen();
    //them thong tien chuc vu va quyen cua chuc vu do

}
QString ManageNV::boolToString(bool t)
{
    if(t)
        return "TRUE";
    else
        return "FALSE";
}

void ManageNV::on_pushButton_3_clicked()
{
    ma_nv = id.getNextIndexCode("nhan_vien","NV");
    if(!query.exec("INSERT INTO nhan_vien(ma_nv, ma_cv, ten_nv, mat_khau, ten_dn, sdt, cmnd, que_quan) "
               "VALUES ('"+ma_nv+"', '"+chucVuModel.index(ui->comboBox_chucVu->currentIndex(),1).data().toString()+"', '"+ui->lineEdit_ten->text()+"', '"+ui->lineEdit_mk->text()+"', '"+ui->lineEdit_tk->text()+"', '"+ui->lineEdit_sdt->text()+"', '"+ui->lineEdit_cmnd->text()+"', '"+ui->lineEdit_qq->text()+"')"))
        qDebug() << "Khong the them nv: " << query.lastQuery();
    else
        testmodel->select();

}
void ManageNV::onCustomContextMenu(const QPoint &point){
    index = ui->tableView->indexAt(point);
    if (index.isValid()) {
        QAction action1("Xóa", this);
        connect(&action1, SIGNAL(triggered()), this, SLOT(xoaMotNhanvien()));
        contextMenu->addAction(&action1);
        contextMenu->exec(ui->tableView->mapToGlobal(point));
    }
}
void ManageNV::xoaMotNhanvien()
{
    testmodel->removeRow(ui->tableView->currentIndex().row());
    testmodel->submitAll();
}
/*su kien chuopt*/


void ManageNV::on_pushButton_5_clicked()
{
    if(phanquyenModel.removeRow(ui->tableView_phanquyen->currentIndex().row()))
    {
        qDebug()<<phanquyenModel.lastError().text();
        if(!phanquyenModel.submitAll())
            qDebug()<<phanquyenModel.lastError().text();
    }
}


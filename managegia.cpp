#include "managegia.h"
#include "ui_managegia.h"


ManageGia::ManageGia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageGia)
{
    ui->setupUi(this);
    click = false;
    ui->treeView_dm->setModel(&dsdanhmuc);
    ui->tableView_giaia->setModel(&test);
    dele = new QSqlRelationalDelegate();
    //dsgiahientai.setQuery("select ten_phu_phi,ma_dm from danh_muc");
    dsdanhmuc.setQuery("select ten_phu_phi,ma_dm from danh_muc");
    test.setTable("danh_muc");
    test.setRelation(0,QSqlRelation("danh_muc","ma_dm","ten_phu_phi"));
    test.select();
    ui->tableView_giaia->setItemDelegate(dele);
    //qDebug() <<test.selectStatement() << test.lastError().text();

    dsdanhmuc.setHeaderData(0,Qt::Horizontal,QString::fromUtf8("Tên phụ phí"));
    dsdanhmuc.setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Mã danh mục"));

    test.setHeaderData(0,Qt::Horizontal,QString::fromUtf8("Mã danh mục"));
    test.setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Giá"));
}

ManageGia::~ManageGia()
{
    delete ui;
    delete dele;
}

void ManageGia::on_lineEdit_gia_returnPressed()
{
    if(click){
        //ma_dm = id.getNextIndexCode("danh_muc","DM");
        if(!query.exec("INSERT INTO don_gia( "
                   "ma_dm, ma_thuoc, gia, ngay) "
                   "VALUES ( '"+ma_dm+"', NULL, '"+ui->lineEdit_gia->text()+"', current_date)"))
        {
            qDebug() << query.lastError().text() << query.lastQuery();
        }
        click = false;
        test.select();
        ui->tableView_giaia->setItemDelegate(dele);
    }
}

void ManageGia::on_lineEdit_dm_returnPressed()
{
    if(!query.exec("INSERT INTO danh_muc( "
                   "ten_phu_phi) "
                   "VALUES ('"+ui->lineEdit_dm->text()+"')"))
        qDebug() << query.lastError().text();
    dsdanhmuc.setQuery("select ten_phu_phi,ma_dm from danh_muc");
}

void ManageGia::on_treeView_dm_clicked(const QModelIndex &index)
{
    click = true;
    if(index.isValid())
    {
        ma_dm = dsdanhmuc.index(index.row(),1).data().toString();
    }
}

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
    test.setTable("don_gia");
    test.setRelation(1,QSqlRelation("danh_muc","ma_dm","ten_phu_phi"));
    test.setFilter("gia = gia_ap_dung");
    test.select();
    ui->tableView_giaia->hideColumn(0);
    ui->tableView_giaia->hideColumn(2);
    ui->tableView_giaia->hideColumn(3);
    ui->tableView_giaia->hideColumn(4);
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
        if(!query.exec("insert into don_gia(ma_dm, ngay, gia) values('"+dsdanhmuc.index(ui->treeView_dm->currentIndex().row(),1).data().toString()+"', current_date , '"+ui->lineEdit_gia->text()+"')"))
        qDebug()<<query.lastError().text();
        else
        {
            query.exec("update don_gia set gia_ap_dung='"+ui->lineEdit_gia->text()+"' where ma_dm='"+dsdanhmuc.index(ui->treeView_dm->currentIndex().row(),1).data().toString()+"'");
            //dsdanhmuc.setQuery("select distinct thuoc.ma_thuoc, ten_thuoc, vung_tiem, dung_tich, gia_ap_dung from thuoc left join don_gia on don_gia.ma_thuoc = thuoc.ma_thuoc");
            ui->lineEdit_gia->clear();
            test.select();
        }
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

void ManageGia::on_pushButton_clicked()
{
    if(!query.exec("INSERT INTO danh_muc( "
                   "ten_phu_phi) "
                   "VALUES ('"+ui->lineEdit_dm->text()+"')"))
        qDebug() << query.lastError().text();
    dsdanhmuc.setQuery("select ten_phu_phi,ma_dm from danh_muc");
}

void ManageGia::on_pushButton_2_clicked()
{

}

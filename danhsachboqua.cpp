#include "danhsachboqua.h"
#include "ui_danhsachboqua.h"

danhSachBoQua::danhSachBoQua(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::danhSachBoQua)
{
    ui->setupUi(this);
    querymodel.setQuery("select * from bo_qua where ngay_bo_qua = current_date()");
    ui->tableView->setModel(&querymodel);
}

danhSachBoQua::~danhSachBoQua()
{
    delete ui;
}

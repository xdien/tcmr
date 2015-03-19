#include "login.h"
#include "ui_login.h"
#include <QtSql>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_buttonBox_accepted()
{
    /*
     * tao mot bang nv_dangnhap "temporay" trong mysql de luu tru id cua nhan vien dang nhap, bang nay se bi xoa kho ngat ket noi toi mysql
    */
    query.exec("create temporary table IF NOT EXISTS nv_dangnhap(ma_nv varchar(12) not null)");
    query.exec("select MA_NV,TEN_DN from NHAN_VIEN where MAT_KHAU = '"+ui->password->text()+"' and  TEN_DN = '"+ui->user->text()+"'");
    if(query.next()){
        ma_nv = query.value(0).toString();
        query.exec("insert into nv_dangnhap values('"+ma_nv+"')");
        if(query.next()){
            qDebug() << "Login succeed";
        }else{
            qDebug() << query.lastError().text() ;
        }
    }else{
        qDebug() << "Login failed";
    }
}

#include "dialog_setting.h"
#include "ui_dialog_setting.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QDomElement>
#include <QFile>
#include <QFileDialog>

Dialog_setting::Dialog_setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_setting)
{
    ui->setupUi(this);
    QSettings loadSet("connect.conf",QSettings::IniFormat);
    loadSet.beginGroup("Default");//set group truoc khi dung
    //set value fro linedialog_*
    ui->linedialog_ip->setText(loadSet.value("ip").toString());
    ui->linedialog_user->setText(loadSet.value("user").toString());
    ui->linedialog_pass->setText(loadSet.value("pass").toString());
    ui->linedialog_db->setText(loadSet.value("db").toString());
    this->setFixedSize(this->maximumSize());
    diaDB = QSqlDatabase::database("qt_sql_default_connection");//lay ket noi toi server hien tai
    ui->toolButton->setVisible(false);
}

Dialog_setting::~Dialog_setting()
{
    delete ui;
}

void Dialog_setting::on_pushButton_clicked()
{   QMessageBox n;
    if(ui->linedialog_db->text() == "" || ui->linedialog_ip->text() == "" || ui->linedialog_pass->text() == "" || ui->linedialog_user->text() == ""){
        n.setText("Chu y: Phai dien day du thong tin");
        n.exec();
    }else{
        //QSqlDatabase::removeDatabase("qt_sql_default_connection");//remove old connect
        if(diaDB.isOpen())
        {
            qDebug() << "Ket sql noi dang duoc mo. Thu ngat ket noi de kiem tra thong so nhap vao";
            diaDB.close();
        }
        diaDB.setHostName(ui->linedialog_ip->text());
        diaDB.setDatabaseName(ui->linedialog_db->text());
        diaDB.setPassword(ui->linedialog_pass->text());
        diaDB.setUserName(ui->linedialog_user->text());
        diaDB.setPort(5432);
        if(diaDB.open()){
            n.setText("Ket noi thanh cong!!");
        } else {
            n.setText("Ket noi that bai");
        }
        n.exec();
    }
    //diaDB.close();
}

void Dialog_setting::on_buttonBox_accepted()
{
    host = ui->linedialog_ip->text();
    user = ui->linedialog_user->text();
    pass = ui->linedialog_pass->text();
    db = ui->linedialog_db->text();
    QSettings settings("connect.conf",QSettings::IniFormat);
    settings.beginGroup("Default");
    settings.setValue("ip",host);
    settings.setValue("user",user);
    settings.setValue("pass",pass);
    settings.setValue("db",db);
    qDebug() << "ok quit";
    /*write_configXML("lietkeDSSV.ncr");
    write_configXML("lietkeTheoKhoa.ncr");
    write_configXML("lietkeTheoTP.ncr");
    write_configXML("printHD.ncr");
    write_configXML("pttientro.ncr");*/
}

void Dialog_setting::write_configXML(const QString fileName)
{
    QString temp;
    temp = dir+"/";//danh cho linux
    temp.append(fileName);
    qDebug()<<temp;
    QFile file(temp);
    if(file.open(QFile::ReadWrite)){
    QDomDocument doc;
    doc.setContent(&file);
    QDomElement docTag = doc.documentElement();
    QDomElement datasourcesTag = docTag.firstChildElement("datasources");
    QDomElement datasourceTag = datasourcesTag.firstChildElement();
    qDebug()<< datasourceTag.tagName();
    datasourceTag.setAttribute("host",host);
    datasourceTag.setAttribute("database",db);
    datasourceTag.setAttribute("user",user);
    datasourceTag.setAttribute("password",pass);
    file.resize(0);
    QTextStream stream;
    stream.setDevice(&file);
    doc.save(stream,4);
    file.close();
    } else {
        qDebug()<<"Khong the read or write file";
    }
}

void Dialog_setting::on_toolButton_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dir = dialog.getExistingDirectory(0,"Caption",QString(),QFileDialog::ShowDirsOnly);
    qDebug()<<dir;
}

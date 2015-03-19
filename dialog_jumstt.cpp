#include "dialog_jumstt.h"
#include "ui_dialog_jumstt.h"

dialog_jumStt::dialog_jumStt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_jumStt)
{
    ui->setupUi(this);
}

dialog_jumStt::~dialog_jumStt()
{
    delete ui;
}

void dialog_jumStt::on_buttonBox_accepted()
{

    query.exec("select * from bo_qua where ngay_bo_qua = current_date() and stt_ = '"+ui->stt->text()+"'");
    if(query.next())
    {
        emit setStt(ui->stt->text());//phat song
    }else{
        ui->thongbao->setText("STT nay khong ton tai");
    }
}


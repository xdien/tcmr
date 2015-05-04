#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    ui->label->setOpenExternalLinks(true);
    ui->label->setText("<a href='https://github.com/xdien/tcmr'>https://github.com/xdien/tcmr</a>");

}

about::~about()
{
    delete ui;
}

void about::on_pushButton_clicked()
{
    this->close();
}

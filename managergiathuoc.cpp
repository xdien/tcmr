#include "managergiathuoc.h"
#include "ui_managergiathuoc.h"

ManagerGiaThuoc::ManagerGiaThuoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerGiaThuoc)
{
    ui->setupUi(this);
}

ManagerGiaThuoc::~ManagerGiaThuoc()
{
    delete ui;
}

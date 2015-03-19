#include "testwg.h"
#include "ui_testwg.h"

testwg::testwg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::testwg)
{
    ui->setupUi(this);
}

testwg::~testwg()
{
    delete ui;
}

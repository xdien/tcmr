#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_setting.h"
#include "tiemngua.h"
#include "test.h"
#include <QMessageBox>
#include <dangkyphieutiem.h>
#include "khamsobo.h"
#include "tiemngua.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSQL_triggered()
{
    Dialog_setting setting;
    setting.exec();
}


void MainWindow::on_actionDan_nhap_triggered()
{
    login * moi;
    moi = new login();
    moi->show();
}

void MainWindow::on_actionPhieu_DK_triggered()
{
    Dangkyphieutiem * modangkyphieutiem;
    modangkyphieutiem = new Dangkyphieutiem();
    ui->mdiArea->addSubWindow(modangkyphieutiem);
    modangkyphieutiem->showMaximized();
}

void MainWindow::on_actionKham_SB_triggered()
{
    khamsobo *moi;
    moi = new khamsobo();
    ui->mdiArea->addSubWindow(moi);
    moi->showMaximized();
}

void MainWindow::on_actionDong_Phi_triggered()
{
    dongphi *dpmoi;
    dpmoi = new dongphi();
    ui->mdiArea->addSubWindow(dpmoi);
    dpmoi->showMaximized();
}

void MainWindow::on_actionTiem_triggered()
{
    tiemngua *ss = new tiemngua();
    ui->mdiArea->addSubWindow(ss);
    ss->showMaximized();
}

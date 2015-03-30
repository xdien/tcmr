#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_setting.h"
#include "tiemngua.h"
#include "test.h"
#include <QMessageBox>
#include <dangkyphieutiem.h>
#include "khamsobo.h"
#include "tiemngua.h"
#include "tracuuphieuhen.h"
#include "managenv.h"
#include "managetiemngua.h"
#include "managechucvu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //db = QSqlDatabase::database("qt_sql_default_connection");
    //connect(db.driver()->,SIGNAL(disconnectNotify()),this,SLOT(trangthaiSQL()));
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
    connect(moi,SIGNAL(setThongBao(QString)),ui->statusBar,SLOT(showMessage(QString)));
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

void MainWindow::on_actionTrC_phieu_hen_triggered()
{
    tracuuPhieuHen *phieuhen;
    phieuhen = new tracuuPhieuHen();
    phieuhen->show();
}

void MainWindow::on_actionQl_nv_triggered()
{
    ManageNV *nv;
    nv = new ManageNV();
    nv->show();
}
void MainWindow::trangthaiSQL()
{
    ui->statusBar->showMessage("ngat ket noi");
}

void MainWindow::on_actionQl_benh_triggered()
{
    ManageTiemNgua *mntiem;
    mntiem = new ManageTiemNgua();
    mntiem->show();
}

void MainWindow::on_actionQL_Chuc_Vu_triggered()
{
    ManageChucVu *chuc_vu;
    chuc_vu = new ManageChucVu();
    chuc_vu->show();
}

void MainWindow::on_actionNhap_thuoc_triggered()
{
    NhapThuoc *nhapthuoc = new NhapThuoc();
    nhapthuoc->show();
}

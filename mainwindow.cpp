#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_setting.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    db = QSqlDatabase::database("qt_sql_default_connection");
    ui->actionPhieu_DK->setEnabled(false);
    ui->actionKham_SB->setEnabled(false);
    ui->actionDong_Phi->setEnabled(false);
    ui->actionTiem->setEnabled(false);
    ui->menuBao_cao->setEnabled(false);
    ui->actionTrC_phieu_hen->setEnabled(false);
    //ui->menuHe_thong->setEnabled(false);//Comment de bao tri
    /*status bar*/
    statusLabel = new QLabel(this);
    tinhtrangsql = new QLabel(this);
    //statusLabel->setText("adsdas");
    //tinhtrangsql->setText("tinh tranf");
    if(db.isOpen())
    {
        tinhtrangsql->setText("Thiết lập kêt nối thành công |");
    }else{
        tinhtrangsql->setText("Không thể kết nối tới máy chủ, xem lại tùy chỉnh kết nối");
    }
    ui->statusBar->addPermanentWidget(tinhtrangsql);
    ui->statusBar->addPermanentWidget(statusLabel);

    /*Khoi dong cac form*/
    moi = new login();
    khamsb = new khamsobo();
    dpmoi = new dongphi();
    tiemn = new tiemngua();
    qlbenhthuoc = new managebenhvathuoc();
    qlGia = new ManageGia();
    modangkyphieutiem = new Dangkyphieutiem();
    connect(moi,SIGNAL(nvdangnhap(QString,QString)),this,SLOT(capnhatPhanQuyen(QString,QString)));
    //connect(moi,)
    //connect(dpmoi,SIGNAL(destroyed(QObject*)),this,SLOT(test(QObject*)));
    //subwindowList = new QList<subwindowList>();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete moi;
    delete khamsb;
    delete dpmoi;
    delete tiemn;
    delete modangkyphieutiem;
    delete qlbenhthuoc;
    delete statusLabel;
    delete tinhtrangsql;
}

void MainWindow::on_actionSQL_triggered()
{
    Dialog_setting setting;
    setting.exec();
}

void MainWindow::on_actionDan_nhap_triggered()
{
    if(!moi->isActiveWindow())
    {
        moi->show();
        moi->activateWindow();
    }
}

void MainWindow::on_actionPhieu_DK_triggered()
{
    if(!modangkyphieutiem->isActiveWindow())
    {
        ui->mdiArea->addSubWindow(modangkyphieutiem);
    }
     modangkyphieutiem->showMaximized();
}

void MainWindow::on_actionKham_SB_triggered()
{
    if(!khamsb->isActiveWindow())
    {
        ui->mdiArea->addSubWindow(khamsb);
        connect(khamsb,SIGNAL(setThongBao(QString)),ui->statusBar,SLOT(showMessage(QString)));
    }
    khamsb->showMaximized();
}

void MainWindow::on_actionDong_Phi_triggered()
{

    if(!dpmoi->isActiveWindow())
    {
        //dpmoi = new dongphi();
        ui->mdiArea->addSubWindow(dpmoi);
        connect(dpmoi,SIGNAL(setThongBao(QString)),ui->statusBar,SLOT(showMessage(QString)));
    }
    dpmoi->showMaximized();
}

void MainWindow::on_actionTiem_triggered()
{
    if(!tiemn->isActiveWindow())
    {
        ui->mdiArea->addSubWindow(tiemn);
        connect(tiemn,SIGNAL(setThongBao(QString)),ui->statusBar,SLOT(showMessage(QString)));
    }
    tiemn->showMaximized();
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

void MainWindow::on_actionTC_cho_tr_em_triggered()
{
    ReportTCTRE *rerportr = new ReportTCTRE();
    rerportr->show();
}

void MainWindow::on_actionBenh_truyen_nhiem_triggered()
{
    ReportBenhTruyenNhiem *benhtruyennhiem = new ReportBenhTruyenNhiem();
    benhtruyennhiem->show();

}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox aa;
    QString aas ="Thong tin ve Qt";
    aa.aboutQt(parentWidget(), aas);
    aa.show();
}
void MainWindow::capnhatPhanQuyen(QString macv, QString manv)//cap nhat phan quyen dua theo macv
{
    query.exec("SELECT dang_ky_tt, kham_so_bo, dong_phi, tiem, bao_cao, he_thong "
               "FROM chuc_vu where ma_cv = '"+macv+"'");
    if(query.next())
    {
        ui->actionPhieu_DK->setEnabled(query.value(0).toBool());
        ui->actionTrC_phieu_hen->setEnabled(query.value(0).toBool());
        ui->actionKham_SB->setEnabled(query.value(1).toBool());
        ui->actionDong_Phi->setEnabled(query.value(2).toBool());
        ui->actionTiem->setEnabled(query.value(3).toBool());
        ui->menuBao_cao->setEnabled(query.value(4).toBool());
        ui->menuHe_thong->setEnabled(query.value(5).toBool());
        //ui->statusBar->showMessage("Danh nhap thanh cong");
        query.exec("select ten_nv from nhan_vien where ma_nv = '"+manv+"'");
        if(query.next())
        {
            statusLabel->setText(query.value(0).toString()+" đã đăng nhập");
        }
    }else{
        ui->statusBar->showMessage("Dang nhap that bai, xin kiem tra thong tin dang nhap");
        qDebug() << "Loi: " <<query.lastError().text();
    }
}


void MainWindow::on_actionQL_B_nh_va_Thu_c_triggered()
{
    if(!qlbenhthuoc->isActiveWindow())
    {
        //ui->mdiArea->addSubWindow(qlbenhthuoc);
    }
    qlbenhthuoc->showMaximized();
}

void MainWindow::on_actionQuan_ly_gia_triggered()
{
    if(!qlGia->isActiveWindow())
    {
        ui->mdiArea->addSubWindow(qlGia);
    }
    qlGia->showMaximized();
}

void MainWindow::on_actionAbout_triggered()
{
    about *a = new about();
    a->show();
}

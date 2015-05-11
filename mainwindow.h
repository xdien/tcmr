#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QMdiSubWindow>
#include <QLabel>
#include "login.h"
#include "dongphi.h"
#include <QtSql>
#include "nhapthuoc.h"
#include <QMessageBox>
#include "khamsobo.h"
#include "tiemngua.h"
#include "tracuuphieuhen.h"
#include "managenv.h"
#include "managetiemngua.h"
#include "managechucvu.h"
#include "reporttctre.h"
#include "reportbenhtruyennhiem.h"
#include <dangkyphieutiem.h>
#include "tiemngua.h"
#include <QObjectList>
#include "managebenhvathuoc.h"
#include "managegia.h"
#include "about.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:

private slots:
    void on_actionSQL_triggered();

    void on_actionDan_nhap_triggered();

    void on_actionPhieu_DK_triggered();

    void on_actionKham_SB_triggered();

    void on_actionDong_Phi_triggered();

    void on_actionTiem_triggered();

    void on_actionTrC_phieu_hen_triggered();

    void on_actionQl_nv_triggered();
    void trangthaiSQL();

    void on_actionQl_benh_triggered();

    void on_actionQL_Chuc_Vu_triggered();

    void on_actionNhap_thuoc_triggered();

    void on_actionTC_cho_tr_em_triggered();

    void on_actionBenh_truyen_nhiem_triggered();

    void on_actionAbout_Qt_triggered();
    void capnhatPhanQuyen(QString macv, QString manv);

    void on_actionQL_B_nh_va_Thu_c_triggered();

    void on_actionQuan_ly_gia_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QSqlQuery query;
    QSqlDatabase db;
    login *moi;
    khamsobo *khamsb;
    dongphi *dpmoi;
    tiemngua *tiemn;
    Dangkyphieutiem *modangkyphieutiem;
    QList<QMdiSubWindow*> subwindowList;
    QObjectList objl;
    managebenhvathuoc *qlbenhthuoc;
    QLabel *statusLabel, *tinhtrangsql;
};

#endif // MAINWINDOW_H

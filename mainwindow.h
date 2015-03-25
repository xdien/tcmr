#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include "login.h"
#include "dongphi.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSQL_triggered();

    void on_actionDan_nhap_triggered();

    void on_actionPhieu_DK_triggered();

    void on_actionKham_SB_triggered();

    void on_actionDong_Phi_triggered();

    void on_actionTiem_triggered();

    void on_actionTrC_phieu_hen_triggered();

    void on_actionQl_nv_triggered();

private:
    Ui::MainWindow *ui;
    QSqlQuery query;
};

#endif // MAINWINDOW_H

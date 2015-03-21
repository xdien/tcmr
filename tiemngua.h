#ifndef TIEMNGUA_H
#define TIEMNGUA_H

#include <QMainWindow>
#include <QtSql>
#include <QDate>
#include <QSqlTableModel>
#include "managerstt.h"
#include "danhsachboqua.h"
#include <QKeyEvent>
#include "dialog_jumstt.h"

namespace Ui {
class tiemngua;
}

class tiemngua : public QMainWindow
{
    Q_OBJECT

public:
    explicit tiemngua(QWidget *parent = 0);
    ~tiemngua();
    void setcurentidx();
public slots:
    void updateMainContent(int stt);
    void infobenh(QString maphieu);
    void infothuoc(QString maphieu);
    void showMuiTiem(QString ma_bnI, QString mat);
    void cleanFroms();
    void receivers_stt(QString stt);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    //su kien nhan nut tren ban phim
    void keyReleaseEvent(QKeyEvent *e);
    void on_actionChon_nguoi_khong_theo_tt_triggered();
    void getID();

    void on_danhsanhcho_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

private:
    QSqlQuery query;
    Ui::tiemngua *ui;
    QDate ngay;
    QString thongbao,ma_phieu;
    //int stt;
    QSqlTableModel muitiem;
    QSqlQueryModel dsthuoc,querymodel,danhsachchomodel;
    QString tiem_thuocID;
    managerSTT *stt;
    QString maphieu;
    QString MaHD;
    QString ma_bn;
    int col,row;
    QModelIndex idx;
};

#endif // TIEMNGUA_H

#ifndef TIEMNGUA_H
#define TIEMNGUA_H
#ifdef __MINGW32__
#include <QtWebKit>
#include <QWebView>
#include <QPrinter>

#endif
#include <QMainWindow>
#include <QtSql>
#include <QDate>
#include <QSqlTableModel>
#include "managerstt.h"
#include "danhsachboqua.h"
#include <QKeyEvent>
#include <QStandardItemModel>
#include <htmltemp.h>

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
    void infobenh(QString maphieu, QString mabn);
    void infothuoc(QString maphieu, QString mabn);
    void showMuiTiem(QString ma_bnI, QString mat);
    void cleanFroms();
    void receivers_stt(QString stt);
    void updateDScho();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    //su kien nhan nut tren ban phim
    void on_actionChon_nguoi_khong_theo_tt_triggered();
    void getID();

    void on_danhsanhcho_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);
    void capnhatDScho(QString notiName);


    void on_pushButton_3_clicked();

private:

    HtmlTemp *htmltemp;
    QSqlQuery query,query_tmp,query_ham;
    Ui::tiemngua *ui;
    QDate ngay;
    QString thongbao,ma_phieu,ma_hoadon;
    //int stt;
    QSqlTableModel muitiem;
    QSqlQueryModel dsthuoc,querymodel,danhsachchomodel;
    QString tiem_thuocID;
    managerSTT *stt;
    QString maphieu,ma_thuoc;
    QString MaHD,ngaytaihen;
    QString ma_bn,stt_lieu;
    QDate ngay_hen;
    int col,row,chu_ky,sl_nhac_lai;
    QModelIndex idx;
    QString tinh_ngayTaiHen(QString mathuoc, QString stt_lieu);
    void capnhatPhieuTiem();
    QStringList  tinh_ngayhentheoDS(QString ma_phieu);
    QString tinhSoTTLieu(QString mathuoc,QString mabn);
    QStandardItemModel item_ngayhen;
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
    QSqlQueryModel danhsachbenh;
    QString strquery;
    QSqlDatabase db;
    void closeEvent(QCloseEvent *event);
    int tmpi;
signals:
    void setThongBao(QString thongbao);



};

#endif // TIEMNGUA_H

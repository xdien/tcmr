#ifndef KHAMSOBO_H
#define KHAMSOBO_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QMenu>
#include <QStandardItemModel>
#include <QtSql>
#include "managerstt.h"
#include <QDate>
#include "manageindex.h"


namespace Ui {
class khamsobo;
}

class khamsobo : public QMainWindow
{
    Q_OBJECT

public:
    explicit khamsobo(QWidget *parent = 0);
    ~khamsobo();
signals:
    void setThongBao(QString thongbao);
private slots:
    void on_pushButton_clicked();

    void on_listView_dsCho_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_treeView_benh_doubleClicked(const QModelIndex &index);

    void on_khongduak_clicked();

    void on_treeView_benhdk_clicked(const QModelIndex &index);

    void on_treeView_thuocgoiY_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

        void codkMoi(QString notiName);

        void on_treeView_dichVu_clicked(const QModelIndex &index);

        void onCustomContextMenu_thuoc(const QPoint &point);
        void onCustomContextMenu_benh(const QPoint &point);
        void onCustomContextMenu_dv(const QPoint &point);
        void xoa_thuoc();
        void xoa_dv();
        void xoa_benh();

private:
    void loaddanhsach_chokham();
    manageIndex id;
    Ui::khamsobo *ui;
    QSqlQuery query,query_notify;
    QSqlQueryModel danhsachCho,danhsachBenhdk,danhsachBenh,danhsach_goiyThuoc,danhsachDV;
    void setcurentidx();
    managerSTT *stt;
    int col,row,sodong,chu_ky;
    QString mot,hai,ba,ma_dv;
    QModelIndex idx;
    QDate ngay_sinh,ngay_hen;
    QString ma_bn,ma_benh,ma_nv,ma_phieu,ma_thuoc,ma_phieuhen,ktimdc,ngay_taihen, co_benh;
    int do_tuoi, thuoc_num;
    QStandardItemModel itemModel_thuocDChon,itemModel_benhDChon, itemModel_dichvu;
    void disableEdit(bool state);
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
    void lapphieuHen(QString mabn, QString manv, QString maPHIEUTIEM, QString mabenh);
    QString tinh_ngayTaiHen(QString mathuoc);
    bool lalandau;
    void loadchitietBN_M(QModelIndex indexx);
    void loadchitietBN_C(QModelIndex indexx);
    QSqlDatabase db;
    QMenu *contextMenu;
    QModelIndex index;
    void closeEvent(QCloseEvent *event);


QList<QStandardItem *> tmp;

};

#endif // KHAMSOBO_H

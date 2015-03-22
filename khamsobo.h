#ifndef KHAMSOBO_H
#define KHAMSOBO_H

#include <QMainWindow>
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

private slots:
    void on_pushButton_clicked();

    void on_listView_dsCho_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_treeView_benh_doubleClicked(const QModelIndex &index);

    void on_khongduak_clicked();

    void on_treeView_benhdk_clicked(const QModelIndex &index);

    void on_treeView_thuocgoiY_clicked(const QModelIndex &index);

private:
    void loaddanhsach_chokham();
    manageIndex id;
    Ui::khamsobo *ui;
    QSqlQuery query;
    QSqlQueryModel danhsachCho,danhsachBenhdk,danhsachBenh,danhsach_goiyThuoc;
    void setcurentidx();
    managerSTT *stt;
    int col,row,sodong,chu_ky;
    QString mot,hai,ba;
    QModelIndex idx;
    QDate ngay_sinh,ngay_hen;
    QString ma_bn,ma_benh,ma_nv,ma_phieu,ma_thuoc,ma_phieuhen,ktimdc,ngay_taihen;
    int do_tuoi, thuoc_num;
    QStandardItemModel itemModel_thuocDChon,itemModel_benhDChon;
    void infoTTbenhNhan(QString ma_phieu);
    void disableEdit(bool state);
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
    void lapphieuHen(QString mabn, QString manv, QString maPHIEUTIEM, QString mabenh);
    QString tinh_ngayTaiHen(QString mathuoc);
    bool lalandau;
};

#endif // KHAMSOBO_H

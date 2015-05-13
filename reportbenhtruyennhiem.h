#ifndef REPORTBENHTRUYENNHIEM_H
#define REPORTBENHTRUYENNHIEM_H

#include <QWidget>
#ifdef __linux
#include "ncreport.h"
#include "ncreportpreviewwindow.h"
#endif

#include "htmltemp.h"
#include <QtSql>
#include <QDebug>
#include <QStandardItemModel>

namespace Ui {
class ReportBenhTruyenNhiem;
}

class ReportBenhTruyenNhiem : public QWidget
{
    Q_OBJECT

public:
    explicit ReportBenhTruyenNhiem(QWidget *parent = 0);
    ~ReportBenhTruyenNhiem();

private slots:
    void on_pushButton_clicked();

    void on_treeView_benh_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_comboBox_tp_currentIndexChanged(int index);

    void on_comboBox_qh_currentIndexChanged(int index);

private:
    HtmlTemp *htmltemp;
    QString tcdd(QString mathuoc, QString madc, QString tu, QString den);
    Ui::ReportBenhTruyenNhiem *ui;
    QSqlQuery query,query_tmp;
    QSqlQueryModel table_benh;
    QString ma_benh,ma_dc,ma_thuoc;
    QStandardItemModel itemModel_benhDChon;
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
    //QString ktcdd(QString mathuoc, QString madc, int sothangtuoinhonhon);
    QList<QStandardItem *> tmp;
    QString ktc(QString mabenh, QString madc, QString tu, QString den);
    QString kr(QString mathuoc, QString madc, QString tu, QString den);
    void setcombobox(QString madc);
    QSqlQueryModel *cmb_tp;
    QString getAdrrCode();
};

#endif // REPORTBENHTRUYENNHIEM_H

#ifndef REPORTTCTRE_H
#define REPORTTCTRE_H

#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QStandardItem>
#include <QPrinter>
#include <QDialog>
//#include "qtrpt.h"
#include <QDebug>
#ifdef __linux
#include "ncreport.h"
#include "ncreportpreviewwindow.h"
#endif
#include "QTextDocument"
#include "htmltemp.h"
namespace Ui {
class ReportTCTRE;
}

class ReportTCTRE : public QWidget
{
    Q_OBJECT

public:
    explicit ReportTCTRE(QWidget *parent = 0);
    ~ReportTCTRE();
signals:
    void setvalue(QString tenbang, QString captren, QString mavung);

private slots:
    void on_comboBox_activated(int index);

    void on_checkBox_toggled(bool checked);

    void on_comboBox_2_activated(int index);
    void setbang(QString tenbang, QString captren, QString mavung);

    void on_listView__diaphuong_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    //QtRPT *report;
    HtmlTemp *htmltemp;
    QSqlQuery query;
    QSqlQueryModel *diachi,*diachiDC,*diachiComBox;
    QString ten_bang,ma_dc;

    QList<QStandardItem *> tmp;
    QStandardItemModel item_tinhthanh, bang1;
    QTextDocument header;
    bool state;
    Ui::ReportTCTRE *ui;
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
    //tao ham kiem tra dung hen, tren lenh 2 ngay so voi ngay hen
    int TestTgianHen(QString mathuoc, QDate ngay_hen,QDate ngay_den_tiem);
    int tongsotre(QString sothang,QString madc,QString mathuoc);
    QString tongsoTreTheoThang(int sothang, QString madc);
    QString tongsoTreTiemTheoThuoc(QString mathuoc, QString madc, int sothangtuoinhohon);
    QString tongsoDoiTuongTheoThuoc2(QString mathuoc, QString madc, int sothangtuoinhohon);
    QString tongsoDoiTuongTheoThuoc3(QString mathuoc, QString madc, int sothangtuoinhohon);
    QString tongSoNguoiTiem(int somui, QString mathuoc, QString madc, int sothangtuoinhohon);
    QString tongsoTreTiemTheothuoc(QString mathuoc, QString madc, int sothangtuoinhohon);
    QString tongsodoiTuongVNNB(QString mathuoc, QString madc, int sothangtuoinhohon);
};

#endif // REPORTTCTRE_H

#ifndef REPORTBENHTRUYENNHIEM_H
#define REPORTBENHTRUYENNHIEM_H

#include <QWidget>
#include "ncreport.h"
#include "ncreportpreviewwindow.h"
#include "htmltemp.h"
#include <QtSql>
#include <QDebug>

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

private:
    HtmlTemp *htmltemp;
    bool kiemtraDungHen(int somui, QString mathuoc, QString madc);
    Ui::ReportBenhTruyenNhiem *ui;
    QSqlQuery query;
};

#endif // REPORTBENHTRUYENNHIEM_H

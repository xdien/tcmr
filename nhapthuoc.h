#ifndef NHAPTHUOC_H
#define NHAPTHUOC_H

#include <QWidget>
#include <QtSql>
#include "manageindex.h"
#include <QMessageBox>

namespace Ui {
class NhapThuoc;
}

class NhapThuoc : public QWidget
{
    Q_OBJECT

public:
    explicit NhapThuoc(QWidget *parent = 0);
    ~NhapThuoc();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_themthuoc_clicked();

    void on_pushButton_luuthuoc_clicked();

private:
    QSqlQuery query;
    manageIndex id;
    QSqlTableModel table_dotuoi;
    QSqlRelationalTableModel *table_thuoc;
    Ui::NhapThuoc *ui;
    void loadTableDoTuoi();
    void loadTableThuoc();
    void insertRow(QSqlTableModel &table_mode);
    void insertRow(QSqlRelationalTableModel *table_model);
    int rowCount;
    QString ma_dt,ma_thuoc;
    QMessageBox mess;
    QSqlRelationalDelegate *sqlde;
};

#endif // NHAPTHUOC_H

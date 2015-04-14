#ifndef MANAGETIEMNGUA_H
#define MANAGETIEMNGUA_H

#include <QKeyEvent>
#include <QWidget>
#include <QtSql>
#include "manageindex.h"

namespace Ui {
class ManageTiemNgua;
}

class ManageTiemNgua : public QWidget
{
    Q_OBJECT

public:
    explicit ManageTiemNgua(QWidget *parent = 0);
    ~ManageTiemNgua();
public slots:
    void insertRow();
private slots:
    void on_pushButton_clicked();
    void up_bang_phongNgua();

    void on_pushButton_2_clicked();

private:
    manageIndex id;
    QString ma_benh;
    QSqlQuery query;
    QSqlTableModel danhsachbenh;
    QSqlRelationalTableModel phong_ngua;
    QSqlRelation rela;
    Ui::ManageTiemNgua *ui;
    QSqlDatabase db;
    void keyPressEvent(QKeyEvent *e);
    int rowCount;
};

#endif // MANAGETIEMNGUA_H

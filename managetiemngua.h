#ifndef MANAGETIEMNGUA_H
#define MANAGETIEMNGUA_H

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
    void on_tableView_phong_pressed(const QModelIndex &index);

private:
    manageIndex id;
    QString ma_benh;
    QSqlQuery query;
    QSqlTableModel danhsachbenh;
    QSqlRelationalTableModel phong_ngua;
    QSqlRelation rela;
    Ui::ManageTiemNgua *ui;
};

#endif // MANAGETIEMNGUA_H

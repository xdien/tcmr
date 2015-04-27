#ifndef MANAGEGIA_H
#define MANAGEGIA_H

#include <QWidget>
#include <QtSql>
#include "manageindex.h"
#include "qlbenhthuoc.h"

namespace Ui {
class ManageGia;
}

class ManageGia : public QWidget
{
    Q_OBJECT

public:
    explicit ManageGia(QWidget *parent = 0);
    ~ManageGia();

private slots:
    void on_lineEdit_gia_returnPressed();

    void on_lineEdit_dm_returnPressed();

    void on_treeView_dm_clicked(const QModelIndex &index);

private:
    QSqlQuery query;
    manageIndex id;
    QString ma_dm;
    Ui::ManageGia *ui;
    bool click;
    QSqlQueryModel dsdanhmuc,dsgiahientai;
    qlbenhthuoc test;
    QSqlRelationalDelegate *dele;
protected:

};

#endif // MANAGEGIA_H

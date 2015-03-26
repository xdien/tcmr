#ifndef MANAGENV_H
#define MANAGENV_H
#include <QtSql>
#include <QWidget>
#include <QKeyEvent>
#include <QStandardItemModel>
#include "manageindex.h"

namespace Ui {
class ManageNV;
}

class ManageNV : public QWidget
{
    Q_OBJECT

public:
    explicit ManageNV(QWidget *parent = 0);
    ~ManageNV();

private slots:
    void on_pushButton_clicked();

private:
    manageIndex id;
    QSqlRelationalTableModel *testmodel;
    Ui::ManageNV *ui;
    void keyPressEvent(QKeyEvent *e);
    QModelIndex model_idx;
    int row;
    QSqlQuery query;
    QString ma_nv,chuc_vu,ten,ten_dn,mk,sdt,cmnd,que_quan;
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
};

#endif // MANAGENV_H

#ifndef DONGPHI_H
#define DONGPHI_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include "manageindex.h"
#include "managerstt.h"

namespace Ui {
class dongphi;
}

class dongphi : public QMainWindow
{
    Q_OBJECT

public:
    explicit dongphi(QWidget *parent = 0);
    ~dongphi();

private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

private:
    Ui::dongphi *ui;
    QSqlQueryModel qrmodel,danhsachthuoc;
    QSqlQuery query;
    QString ma_bn,ma_hd;
    QString ma_phieu,ma_nv;
    manageIndex id;

    int stt;
    managerSTT *stt_hd;
};

#endif // DONGPHI_H

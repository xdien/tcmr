#ifndef DONGPHI_H
#define DONGPHI_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QCloseEvent>
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
signals:
    void setThongBao(QString);
private slots:

    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_6_clicked();
    void capnhatDScho();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_returnPressed();
//    void

private:
  void closeEvent(QCloseEvent *event);
    Ui::dongphi *ui;
    QSqlQueryModel qrmodel,danhsachthuoc,dsdichvu;
    QSqlQuery query;
    QString ma_bn,ma_hd;
    QString ma_phieu,ma_nv;
    manageIndex id;
    QSqlDatabase db;
    int stt;
    managerSTT *stt_hd;
    QModelIndex idx;
};

#endif // DONGPHI_H

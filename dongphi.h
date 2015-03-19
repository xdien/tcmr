#ifndef DONGPHI_H
#define DONGPHI_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>

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
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

private:
    Ui::dongphi *ui;
    QSqlQueryModel qrmodel;
    QSqlQuery query;
    QString ma_bn;
    QString ma_phieu,ma_nv;
    int ma_hd,stt;
};

#endif // DONGPHI_H

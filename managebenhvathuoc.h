#ifndef MANAGEBENHVATHUOC_H
#define MANAGEBENHVATHUOC_H

#include <QMainWindow>
#include <QtSql>
#include <QStandardItem>
#include "manageindex.h"
#include <QMenu>

namespace Ui {
class managebenhvathuoc;
}

class managebenhvathuoc : public QMainWindow
{
    Q_OBJECT

public:
    explicit managebenhvathuoc(QWidget *parent = 0);
    ~managebenhvathuoc();

private slots:
    void on_tableView_dsbenh_clicked(const QModelIndex &index);

    void on_lineEdit_returnPressed();

    void on_pushButton_themdotuoi_clicked();

    void on_pushButton_themthuoc_clicked();

    void on_tableView_dsthuoc_doubleClicked(const QModelIndex &index);
    void onCustomContextMenu(const QPoint &point);
    void xoathuocthuocbenh();

    void on_pushButton_timkiem_clicked();

    void on_lineEdit_tkthuoc_textChanged(const QString &arg1);

private:
    Ui::managebenhvathuoc *ui;
    QSqlQueryModel dsbenhmodel;
    QSqlQueryModel dsthuocmodel;
    QSqlQueryModel benhdcchonmodel;
    QSqlQueryModel dotuoimodel;


    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
    bool eventFilter(QObject *obj, QEvent *event);
    QString maBn;
    QSqlQuery query;
    manageIndex id;
    QString lavx;
    QString dotuoi;
    QString mabenh;
    QMenu *contextMenu;
    QModelIndex index;
    QString mathuoc;


};

#endif // MANAGEBENHVATHUOC_H

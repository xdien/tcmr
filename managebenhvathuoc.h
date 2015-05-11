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
    void onCustomContextMenu_benh(const QPoint &point);
    void onCustomContextMenu_thuoc(const QPoint &point);
    void xoathuocthuocbenh();

    void on_lineEdit_tkthuoc_textChanged(const QString &arg1);
    void xoa_benh();
    void xoa_thuoc();

    void on_pushButton_capnhatgia_clicked();

    void on_lineEdit_2_returnPressed();

private:
    Ui::managebenhvathuoc *ui;
    QSqlQueryModel dsbenhmodel;
    QSqlQueryModel dsthuocmodel;
    QSqlQueryModel benhdcchonmodel;
    QSqlQueryModel dotuoimodel;

    bool tkFocus;

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

    QStandardItemModel itemLichhen;
    int tuTang;
    QString maLh;

};

#endif // MANAGEBENHVATHUOC_H

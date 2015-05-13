#ifndef TRACUUPHIEUHEN_H
#define TRACUUPHIEUHEN_H

#include <QStandardItemModel>
#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QMenu>
#include "managerstt.h"

namespace Ui {
class tracuuPhieuHen;
}

class tracuuPhieuHen : public QWidget
{
    Q_OBJECT

public:
    explicit tracuuPhieuHen(QWidget *parent = 0);
    ~tracuuPhieuHen();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_dsbenh_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_ma_bn_textChanged(const QString &arg1);

    void onCustomContextMenu(const QPoint &point);
    void xoaThuoc();

private:
    Ui::tracuuPhieuHen *ui;
    QSqlQuery query;
    QStandardItemModel itemtDSbenh, itemtDSthuoc,thuocModel;
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
    int mui_tiem,stt_benh;
    QString ma_bn,ma_benh;
    QSqlQueryModel danhsachgoiYBenh;
    managerSTT *stt;
    QList<QStandardItem *> tmp;
    QStringList dsbenhmoi;
    QModelIndex index;
    QMenu *contextMenu;
};

#endif // TRACUUPHIEUHEN_H

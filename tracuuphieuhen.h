#ifndef TRACUUPHIEUHEN_H
#define TRACUUPHIEUHEN_H

#include <QStandardItemModel>
#include <QWidget>
#include <QtSql>
#include <QDebug>
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

private:
    Ui::tracuuPhieuHen *ui;
    QSqlQuery query;
    QStandardItemModel itemtDSbenh, itemtDSthuoc;
    QSqlQueryModel thuocModel;
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
    int mui_tiem,stt_benh;
    QString ma_bn;
    managerSTT *stt;
};

#endif // TRACUUPHIEUHEN_H

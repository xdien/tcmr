#ifndef TRACUUPHIEUHEN_H
#define TRACUUPHIEUHEN_H

#include <QStandardItemModel>
#include <QWidget>
#include <QtSql>
#include <QDebug>

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

private:
    Ui::tracuuPhieuHen *ui;
    QSqlQuery query;
    QStandardItemModel itemtDSbenh, itemtDSthuoc;
    QSqlQueryModel thuocModel;
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
};

#endif // TRACUUPHIEUHEN_H

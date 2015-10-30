#ifndef MANAGECHUCVU_H
#define MANAGECHUCVU_H

#include <QKeyEvent>
#include <QWidget>
#include <QtSql>
#include "manageindex.h"
#include <QDebug>

namespace Ui {
class ManageChucVu;
}

class ManageChucVu : public QWidget
{
    Q_OBJECT

public:
    explicit ManageChucVu(QWidget *parent = 0);
    ~ManageChucVu();

private slots:
    void on_pushButton_clicked();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    manageIndex id;
    QString ma_cv;
    QSqlQuery query;
    QSqlTableModel *tablemodel;
    QSqlRelationalTableModel *chuc_vu;
    Ui::ManageChucVu *ui;
    void keyPressEvent(QKeyEvent *e);
    void update_phanquyen();
};

#endif // MANAGECHUCVU_H

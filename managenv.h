#ifndef MANAGENV_H
#define MANAGENV_H
#include <QtSql>
#include <QWidget>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <QMenu>
#include "manageindex.h"
#include <QCheckBox>
#include <QAction>

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

    void LoadChucvu();

    void on_comboBox_chucVu_currentIndexChanged(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void onCustomContextMenu(const QPoint &point);
    void xoaMotNhanvien();
signals:
    void focussed(bool hasFocus);
private:
    manageIndex id;
    QSqlRelationalTableModel *testmodel, *chuc_vumodel;
    Ui::ManageNV *ui;
    void keyPressEvent(QKeyEvent *e);
    QModelIndex model_idx;
    int row;
    QSqlQuery query;
    QString ma_cv,ma_nv,chuc_vu,ten,ten_dn,mk,sdt,cmnd,que_quan;
    QList<QStandardItem *> prepareRow(const QString &first,
                                                    const QString &second,
                                                    const QString &third);
   void LoadCheckbox(QString macv, QCheckBox *c1, QCheckBox *c2, QCheckBox *c3, QCheckBox *c4, QCheckBox *c5);
   QSqlQueryModel chucVuModel;
   void LoadtableQuyen();
   QSqlRelationalDelegate *dele;
   QMenu *contextMenu;
   QString boolToString(bool t);
   QModelIndex index;
   bool eventFilter(QObject *obj, QEvent *event);
protected:
};

#endif // MANAGENV_H

#ifndef DANGKYPHIEUTIEM_H
#define DANGKYPHIEUTIEM_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QtSql>
#include <QStandardItemModel>
#include "manageindex.h"

namespace Ui {
class Dangkyphieutiem;
}

class Dangkyphieutiem : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Dangkyphieutiem(QWidget *parent = 0);
    ~Dangkyphieutiem();
    
private slots:
    void on_comboBox_tp_currentIndexChanged(int index);

    void on_comboBox_qh_currentIndexChanged(int index);

    void on_listView_benh_clicked(const QModelIndex &index);

    void on_luu_tt_clicked();

    void on_pushButton_2_clicked();

    void on_listView_benh_doubleClicked(const QModelIndex &index);

private:
    Ui::Dangkyphieutiem *ui;
    QString thuocdiachi(QString nhapvao);
    void setcombobox(QString madc);
    void loadDefaultarr();
    void loadTP();
    QString ma_dc,ten_bn,ma_thuoc, gioitinh, ma_nv,ma_bn,ma_pt;
    int stt_lieu,thuoc_num;
    QSqlQuery query;
    //su dung model cho cmb_tp vi khog lam viec thong thuog
    QSqlQueryModel *cmb_tp;
    QSqlQueryModel *list_benh;
    QSqlQueryModel *table_thuoc;
    QString table_name;
    //lay ma dia chi tu combox
    QString getAdrrCode();
    QString getSex();
     QStandardItemModel itemModel;
     QList<QStandardItem *> prepareRow(const QString &first, const QString &second, const QString &third);
     QList<QStandardItem *> preparedRow;
     QString mot,hai,ba;
     manageIndex id;
};

#endif // DANGKYPHIEUTIEM_H

#ifndef DANHSACHBOQUA_H
#define DANHSACHBOQUA_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class danhSachBoQua;
}

class danhSachBoQua : public QDialog
{
    Q_OBJECT

public:
    explicit danhSachBoQua(QWidget *parent = 0);
    ~danhSachBoQua();

private:
    Ui::danhSachBoQua *ui;
    QSqlQueryModel querymodel;
};

#endif // DANHSACHBOQUA_H

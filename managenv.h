#ifndef MANAGENV_H
#define MANAGENV_H
#include <QtSql>
#include <QWidget>

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

private:
    QSqlRelationalTableModel *testmodel;
    Ui::ManageNV *ui;
};

#endif // MANAGENV_H

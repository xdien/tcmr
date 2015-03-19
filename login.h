#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_buttonBox_accepted();

private:
    QSqlQuery query;
    Ui::login *ui;
    QString ma_nv;
};

#endif // LOGIN_H

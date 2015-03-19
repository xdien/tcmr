#ifndef DIALOG_JUMSTT_H
#define DIALOG_JUMSTT_H

#include <QDialog>
#include <QSqlQuery>
namespace Ui {
class dialog_jumStt;
}

class dialog_jumStt : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_jumStt(QWidget *parent = 0);
    ~dialog_jumStt();
signals:
    void setStt(QString stt);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::dialog_jumStt *ui;
    QSqlQuery query;
};

#endif // DIALOG_JUMSTT_H

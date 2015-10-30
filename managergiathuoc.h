#ifndef MANAGERGIATHUOC_H
#define MANAGERGIATHUOC_H

#include <QWidget>

namespace Ui {
class ManagerGiaThuoc;
}

class ManagerGiaThuoc : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerGiaThuoc(QWidget *parent = 0);
    ~ManagerGiaThuoc();

private:
    Ui::ManagerGiaThuoc *ui;
};

#endif // MANAGERGIATHUOC_H

#ifndef TESTWG_H
#define TESTWG_H

#include <QWidget>

namespace Ui {
class testwg;
}

class testwg : public QWidget
{
    Q_OBJECT

public:
    explicit testwg(QWidget *parent = 0);
    ~testwg();

private:
    Ui::testwg *ui;
};

#endif // TESTWG_H

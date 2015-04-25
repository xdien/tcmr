#ifndef QLBENHTHUOC_H
#define QLBENHTHUOC_H
#include <QtSql>


class qlbenhthuoc: public QSqlRelationalTableModel
{
public:
    qlbenhthuoc();
    ~qlbenhthuoc();
    void setQuery(QString query);
    virtual QString selectStatement() const;
private:

    QString str;

};

#endif // QLBENHTHUOC_H

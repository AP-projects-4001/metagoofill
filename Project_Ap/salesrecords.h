#ifndef SALESRECORDS_H
#define SALESRECORDS_H
#include "customer.h"
#include <QDialog>
#include "factor.h"
namespace Ui {
class SalesRecords;
}

class SalesRecords : public QDialog
{
    Q_OBJECT

public:
    explicit SalesRecords(QWidget *parent = nullptr);
    ~SalesRecords();
    void search_in_sells();
private:
    Ui::SalesRecords *ui;
    customer cust;
    Factor factors[9];

    int number_mysells;

    int ptr_start_mysells;

    int len_search;

    int end_part_sells;

    int count;
};

#endif // SALESRECORDS_H

#ifndef SALESRECORDS_H
#define SALESRECORDS_H
#include "customer.h"
#include <QDialog>
#include "factor.h"
using namespace std;
namespace Ui {
class SalesRecords;
}

class SalesRecords : public QDialog
{
    Q_OBJECT

public:
    explicit SalesRecords(customer,QWidget *parent = nullptr);
    ~SalesRecords();
    void search_in_sells(string&);

    void show_sells(string&);
private:
    Ui::SalesRecords *ui;
    customer cust;
    Factor factor;
};

#endif // SALESRECORDS_H

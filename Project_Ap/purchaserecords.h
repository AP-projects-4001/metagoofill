#ifndef PURCHASERECORDS_H
#define PURCHASERECORDS_H
#include "client.h"
#include <QDialog>
#include "factor.h"
#include "customer.h"
#include "product.h"

using namespace std;
namespace Ui {
class PurchaseRecords;
}

class PurchaseRecords : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseRecords(client,QWidget *parent = nullptr);
    ~PurchaseRecords();

    void search_in_buys(string&);

    void show_buys(string&);

    void go_to_factor(int);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::PurchaseRecords *ui;
    client clie;
    Factor factor;
    customer cust;
    Product product;
};

#endif // PURCHASERECORDS_H

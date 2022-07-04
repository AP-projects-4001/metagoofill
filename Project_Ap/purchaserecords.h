#ifndef PURCHASERECORDS_H
#define PURCHASERECORDS_H
#include <client.h>
#include <QDialog>
#include "factor.h"
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

private:
    Ui::PurchaseRecords *ui;
    client clie;
    Factor factor;
};

#endif // PURCHASERECORDS_H

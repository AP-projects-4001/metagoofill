#ifndef PURCHASERECORDS_H
#define PURCHASERECORDS_H
#include <client.h>
#include <QDialog>
#include "factor.h"

namespace Ui {
class PurchaseRecords;
}

class PurchaseRecords : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseRecords(QWidget *parent = nullptr);
    ~PurchaseRecords();

    void search_in_buys();

    void next_to_search(int);

    void preview_to_search(int);

private:
    Ui::PurchaseRecords *ui;
    client clie;
    Factor factors[9];
    int number_mybuys;
    int ptr_start_mybuys;


    int len_search;

    int end_part_buys;

    int count;
};

#endif // PURCHASERECORDS_H

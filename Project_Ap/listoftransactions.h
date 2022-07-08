#ifndef LISTOFTRANSACTIONS_H
#define LISTOFTRANSACTIONS_H

#include <QDialog>
#include "client.h"
#include "customer.h"
#include "product.h"
#include "factor.h"

namespace Ui {
class listoftransactions;
}

class listoftransactions : public QDialog
{
    Q_OBJECT

public:
    explicit listoftransactions(QWidget *parent = nullptr);
    ~listoftransactions();

    void search_in_factors(string&);

    void show_factors(string&);

private slots:
    void on_pushButton_clicked();

private:
    Ui::listoftransactions *ui;
    Factor factor;
    client clie;
    customer cust;
    Product product;
};

#endif // LISTOFTRANSACTIONS_H

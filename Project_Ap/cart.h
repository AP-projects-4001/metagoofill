#ifndef CART_H
#define CART_H

#include <QDialog>
#include "choosepay.h"
#include "paymentgateway.h"
#include "topupwallet.h"
#include "factor.h"
#include "product.h"
#include "client.h"

namespace Ui {
class cart;
}

class cart : public QDialog
{
    Q_OBJECT

public:
    explicit cart(QWidget *parent = nullptr);
    ~cart();

private slots:
    void on_pushButton_filter_clicked();

    void rec_method(bool);

    void  add_to_factor();

    void add_to_buys();

    void  add_to_sells();

private:
    Ui::cart *ui;
    choosepay *payMethod;
    int numOfProducts;
    Factor factor;
    Product product;
    client clie;
    int number_factors;
    int number_mybuys;
    int number_mysells;
    int number_buys;
    int number_sells;
    int ptr_start_mybuys;
    int ptr_end_mybuys;
    int ptr_start_mysells;
    int ptr_end_mysells;
};

#endif // CART_H

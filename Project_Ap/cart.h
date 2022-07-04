#ifndef CART_H
#define CART_H

#include <QDialog>
#include "choosepay.h"
#include "paymentgateway.h"
#include "topupwallet.h"
#include "factor.h"
#include "product.h"
#include "client.h"
#include "customer.h"

namespace Ui {
class cart;
}

class cart : public QDialog
{
    Q_OBJECT

public:
    explicit cart(client,QWidget *parent = nullptr);
    ~cart();

    void  add_to_factor();

    void add_to_buys();

    void  add_to_sells();

    void start_cart();

    void next_to_cart(int);

    void preview_to_cart(int);

    void show_cart();

    void transaction();

private slots:
    void on_pushButton_filter_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_prev_clicked();

    void rec_method(bool);

private:
    Ui::cart *ui;
    choosepay *payMethod;
    customer cust;
    client clie;
    Factor factor;
    Product product;
    Product products[9];
    int number[9];
    int numOfProducts;
    int number_factors;
    int number_buys;
    int number_sells;

    int end_part_cart;
    int count;
    int len_cart;
};

#endif // CART_H

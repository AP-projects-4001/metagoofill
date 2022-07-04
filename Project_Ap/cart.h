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
    explicit cart(client,QWidget *parent = nullptr);
    ~cart();

    void  add_to_factor();

    void add_to_buys();

    void  add_to_sells();

    void next_to_cart(int);

    void preview_to_cart(int);

    void show_cart();

private slots:
    void rec_method(bool);

    void on_pushButton_filter_clicked();

private:
    Ui::cart *ui;
    choosepay *payMethod;
    client clie;
    int numOfProducts;
    Factor factor;
    Factor factors[9];
    Product product;
    int number_factors;
    int number_mybuys;
    int number_mysells;
    int number_buys;
    int number_sells;
    int ptr_start_mybuys;
    int ptr_end_mybuys;
    int ptr_start_mysells;
    int ptr_end_mysells;
    int end_part_cart;
    int count;
    int len_cart;
};

#endif // CART_H

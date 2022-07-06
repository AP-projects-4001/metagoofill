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
#include "ui_cart.h"

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

    void repet_to_search(int);

    void delete_product(int);

    void save_number_orders();

    int status_product(Product&,int);

    void show_cart();

    void show_status(QLabel*,int);

    bool status_cart();

    void delete_cart();

    void reserve_products();

    void cansel_reserve_products();

    void transaction();

private slots:
    void on_pushButton_next_clicked();

    void on_pushButton_prev_clicked();

    void on_pushButton_filter_3_clicked();

    void on_pushButton_filter_clicked();

    void on_pushButton_filter_2_clicked();

    void rec_method(bool);

    void status_payment(bool );

    void on_pushButton_filter_4_clicked();

private:
    Ui::cart *ui;
    customer cust;
    client clie;
    Factor factor;
    Product product;
    Product products[9];
    int number[9];
    int flag_status[9];
    int prices[20];
    int number_factors;

    int end_part_cart;
    int count;
    int len_cart;
    bool flag_cart;
    int sum;
};

#endif // CART_H

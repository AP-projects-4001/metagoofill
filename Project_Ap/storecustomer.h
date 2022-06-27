#ifndef STORECUSTOMER_H
#define STORECUSTOMER_H
#include "product.h"
#include "customer.h"
#include <QDialog>

namespace Ui {
class storecustomer;
}

class storecustomer : public QDialog
{
    Q_OBJECT

public:
    explicit storecustomer(customer,QWidget *parent = nullptr);
    ~storecustomer();

private slots:
    void on_pushButten_add_clicked();

    void on_pushButten_delete_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_before_clicked();

    void item_added(bool,bool,bool,bool);

    void item_added2(QString,QString,QString,QString,QString,QString,QString,bool,bool,bool,bool);


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::storecustomer *ui;
    int number_myproducts;
    int count_myproduct;
    int ptr_file_myproduct;
    Product product;
    Product product2;
    int number_products;
    int ptr_file_this_myproduct;
    customer cust;

    int ptr_start_file_product_type;
    int ptr_end_file_product_type;
    int number_product_type;
private:
    void show_product();
    int go_to_product(int);
    void save_product();
    void add_product();
    void delete_product();
    void show_without_product();
    void add_product_to_type();
};

#endif // STORECUSTOMER_H

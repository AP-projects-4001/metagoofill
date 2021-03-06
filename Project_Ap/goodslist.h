#ifndef GOODSLIST_H
#define GOODSLIST_H

#include <QDialog>
#include "clothes_filter_info.h"
#include "fruitandveg_filter_info.h"
#include "others_filter_info.h"
#include "product.h"//
#include "gooddetails.h"
#include "client.h"
namespace Ui {
class goodsList;
}

class goodsList : public QDialog
{
    Q_OBJECT

public:
    explicit goodsList(client,QWidget *parent = nullptr);
    ~goodsList();

    void search_by_filter_in_products();

    void delete_search();

    void next_to_search(int);

    void preview_to_search(int);

    bool filter();

    void show_list_products();

    bool add_to_cart(int ,int);


private slots:
    void recG_type(int);

    void on_pushButton_filter_clicked();

    void rec_clothes_info(clothes_filter_info);

    void rec_fruit_info(fruitandveg_filter_info);

    void rec_other_info(others_filter_info);

    void on_pushButton_next_clicked();

    void on_pushButton_prev_clicked();

    void on_pushButton_g1_clicked();

    void on_pushButton_g2_clicked();

    void on_pushButton_g3_clicked();

    void on_pushButton_g4_clicked();

    void on_pushButton_g5_clicked();

    void on_pushButton_g6_clicked();

    void on_pushButton_g7_clicked();

    void on_pushButton_g8_clicked();

    void on_pushButton_g9_clicked();

    void on_pushButton_filter_3_clicked();

    void on_pushButton_filter_2_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_filter_4_clicked();

    void on_pushButton_filter_5_clicked();

    void on_pushButton_filter_6_clicked();

private:
    Ui::goodsList *ui;
    client clie;
    clothes_filter_info clothes_info_2;
    fruitandveg_filter_info fruit_info_2;
    others_filter_info other_info_2;
    goodDetails *details;
    int type ;
    Product products[9];
    Product product;
    int end_part_products;
    int len_search;
    int count;
    bool flag_filter;

    int start_search;
    int number_search;
};

#endif // GOODSLIST_H

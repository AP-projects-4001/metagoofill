#ifndef GOODSLIST_H
#define GOODSLIST_H

#include <QDialog>
#include "clothes_filter_info.h"
#include "fruitandveg_filter_info.h"
#include "others_filter_info.h"
#include "product.h"//

namespace Ui {
class goodsList;
}

class goodsList : public QDialog
{
    Q_OBJECT

public:
    explicit goodsList(QWidget *parent = nullptr);
    ~goodsList();

private slots:
    void recG_type(int);

    void on_pushButton_filter_clicked();

    void rec_clothes_info(clothes_filter_info);

    void rec_fruit_info(fruitandveg_filter_info);

    void rec_other_info(others_filter_info);

    void search_by_filter();//

    void next_to_search(int);//

    void preview_to_search(int);//

    bool filter();//

    void show_list_products();

    void on_pushButton_next_clicked();

    void on_pushButton_prev_clicked();

private:
    Ui::goodsList *ui;
    clothes_filter_info clothes_info_2;
    fruitandveg_filter_info fruit_info_2;
    others_filter_info other_info_2;
    int type ;
    Product products[9];//
    Product product;//
    int end_part_products;//
    int len_search;//
    int count=0;
};

#endif // GOODSLIST_H

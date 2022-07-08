#ifndef GROUPINGGOODS_H
#define GROUPINGGOODS_H

#include <QDialog>
#include "client.h"

namespace Ui {
class groupingGoods;
}

class groupingGoods : public QDialog
{
    Q_OBJECT

public:
    explicit groupingGoods(client _clie, QWidget *parent = nullptr);
    ~groupingGoods();

signals:
    void G_type(int);

private slots:
    void on_technology_clicked();

    void on_homeApp_clicked();

    void on_clothes_clicked();

    void on_fruit_clicked();

    void on_supermarket_clicked();

    void on_nuts_clicked();

    void on_popular_clicked();

    void on_profile_clicked();

    void on_cart_clicked();

private:
    Ui::groupingGoods *ui;
    client clie;

};

#endif // GROUPINGGOODS_H

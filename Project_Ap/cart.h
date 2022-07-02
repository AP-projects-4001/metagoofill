#ifndef CART_H
#define CART_H

#include <QDialog>
#include "choosepay.h"
#include "paymentgateway.h"
#include "topupwallet.h"

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

private:
    Ui::cart *ui;
    choosepay *payMethod;
    int numOfProducts;
};

#endif // CART_H

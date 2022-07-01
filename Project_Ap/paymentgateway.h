#ifndef PAYMENTGATEWAY_H
#define PAYMENTGATEWAY_H

#include <QDialog>

namespace Ui {
class PaymentGateWay;
}

class PaymentGateWay : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentGateWay(int price, QWidget *parent = nullptr);
    ~PaymentGateWay();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PaymentGateWay *ui;
    int prc;
};

#endif // PAYMENTGATEWAY_H

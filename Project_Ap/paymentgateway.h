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
    explicit PaymentGateWay(QWidget *parent = nullptr);
    ~PaymentGateWay();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PaymentGateWay *ui;
};

#endif // PAYMENTGATEWAY_H

#ifndef CHOOSEPAY_H
#define CHOOSEPAY_H

#include <QDialog>
#include "client.h"
namespace Ui {
class choosepay;
}

class choosepay : public QDialog
{
    Q_OBJECT

public:
    explicit choosepay(int _sum,client _clie,QWidget *parent = nullptr);
    ~choosepay();

signals:
    void send_method(bool);
    void send_status_payment_from_wallet(bool);

private slots:
    void on_pushButton_difectpay_clicked();

    void on_pushButton_wallet_clicked();

    void on_pushButton_wallet_2_clicked();

    void on_pushButton_refuse_clicked();

private:
    Ui::choosepay *ui;
    bool method;
    client clie;
    int sum;
};

#endif // CHOOSEPAY_H

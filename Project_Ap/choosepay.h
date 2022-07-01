#ifndef CHOOSEPAY_H
#define CHOOSEPAY_H

#include <QDialog>

namespace Ui {
class choosepay;
}

class choosepay : public QDialog
{
    Q_OBJECT

public:
    explicit choosepay(QWidget *parent = nullptr);
    ~choosepay();

signals:
    void send_method(bool);

private slots:
    void on_pushButton_difectpay_clicked();

    void on_pushButton_wallet_clicked();

private:
    Ui::choosepay *ui;
    bool method;
};

#endif // CHOOSEPAY_H

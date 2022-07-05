#ifndef TOPUPWALLET_H
#define TOPUPWALLET_H

#include <QDialog>
#include "client.h"

namespace Ui {
class TopUpWallet;
}

class TopUpWallet : public QDialog
{
    Q_OBJECT

public:
    explicit TopUpWallet(client, QWidget *parent = nullptr);
    ~TopUpWallet();

private slots:
    void on_pushButton_clicked();
    void Charging_success(bool);
    void on_pushButton_refuse_clicked();

private:
    Ui::TopUpWallet *ui;
    client clie;
    int AmountOfInventoryincrease;
};

#endif // TOPUPWALLET_H

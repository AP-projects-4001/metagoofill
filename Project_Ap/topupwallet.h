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

private:
    Ui::TopUpWallet *ui;
    client clie;
};

#endif // TOPUPWALLET_H

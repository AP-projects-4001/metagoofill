#ifndef TOPUPWALLET_H
#define TOPUPWALLET_H

#include <QDialog>

namespace Ui {
class TopUpWallet;
}

class TopUpWallet : public QDialog
{
    Q_OBJECT

public:
    explicit TopUpWallet(QWidget *parent = nullptr);
    ~TopUpWallet();

private:
    Ui::TopUpWallet *ui;
};

#endif // TOPUPWALLET_H

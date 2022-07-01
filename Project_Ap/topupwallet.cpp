#include "topupwallet.h"
#include "ui_topupwallet.h"

TopUpWallet::TopUpWallet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopUpWallet)
{
    ui->setupUi(this);
}

TopUpWallet::~TopUpWallet()
{
    delete ui;
}

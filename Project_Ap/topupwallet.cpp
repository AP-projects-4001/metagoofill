#include "topupwallet.h"
#include "ui_topupwallet.h"

TopUpWallet::TopUpWallet(client _clie, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopUpWallet)
{
    clie=_clie;
    ui->setupUi(this);
}

TopUpWallet::~TopUpWallet()
{
    delete ui;
}

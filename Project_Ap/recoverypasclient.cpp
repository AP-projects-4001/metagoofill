#include "recoverypasclient.h"
#include "ui_recoverypasclient.h"
#include "forgetpasclient.h"
RecoveryPasClient::RecoveryPasClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoveryPasClient)
{
    ui->setupUi(this);
}

RecoveryPasClient::~RecoveryPasClient()
{
    delete ui;
}

void RecoveryPasClient::on_pushButton_2_clicked()
{
    ForgetPasClient *p = new ForgetPasClient(this);
    p->show();
    this->hide();
}

void RecoveryPasClient::on_pushButton_clicked()
{
    //Must complete by Ali Yaghini
}

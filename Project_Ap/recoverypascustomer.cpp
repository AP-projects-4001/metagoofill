#include "recoverypascustomer.h"
#include "ui_recoverypascustomer.h"
#include "forgetpascustomer.h"
RecoveryPasCustomer::RecoveryPasCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoveryPasCustomer)
{
    ui->setupUi(this);
}

RecoveryPasCustomer::~RecoveryPasCustomer()
{
    delete ui;
}

void RecoveryPasCustomer::on_pushButton_clicked()
{
    emit PassingTheCustomerPassword(ui->textEdit->toPlainText());
    QMessageBox::information(this, "توجه", "رمز تغییر یافت");
    close();
}

void RecoveryPasCustomer::on_pushButton_2_clicked()
{
    ForgetPasCustomer *p = new ForgetPasCustomer(this);
    p->show();
    this->hide();
}

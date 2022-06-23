#include "forgetpascustomer.h"
#include "ui_forgetpascustomer.h"
#include "recoverypascustomer.h"
#include "customerlogin.h"
#include "mainlogin.h"
#include<QMessageBox>
using namespace std;
ForgetPasCustomer::ForgetPasCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgetPasCustomer)
{
    ui->setupUi(this);
}
bool MatchingUserAndCellCustomer(string user,string Number)
{
    return true;
}
ForgetPasCustomer::~ForgetPasCustomer()
{
    delete ui;
}

void ForgetPasCustomer::on_pushButton_clicked()
{
    string User = ui->textEdit->toPlainText().toStdString();//User Name
    string Cell = ui->textEdit_2->toPlainText().toStdString();//CellPhone Number
    if(MatchingUserAndCellCustomer(User,Cell)&&User!=""&&Cell!="")
    {
        RecoveryPasCustomer *p = new RecoveryPasCustomer(this);
        p->show();
    }
    else
    {
        QMessageBox::about(this,"توجه","یوزر یا شماره تلفن تطابقت نداردیا دو جایگاه خالیست");
        return;
    }
}

void ForgetPasCustomer::on_pushButton_2_clicked()
{
    CustomerLogin *p = new CustomerLogin(this);
    p->show();
    this->hide();
}

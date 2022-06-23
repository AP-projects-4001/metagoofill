#include "forgetpasclient.h"
#include "ui_forgetpasclient.h"
#include "loginclient.h"
#include "recoverypasclient.h"
#include <QMessageBox>
using namespace  std;
ForgetPasClient::ForgetPasClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgetPasClient)
{
    ui->setupUi(this);
}
bool MatchingUserAndCellClient(string User,string Cell)
{
    return true;//Complete By Ali yaghini
}
ForgetPasClient::~ForgetPasClient()
{
    delete ui;
}

void ForgetPasClient::on_pushButton_2_clicked()
{
    LoginClient *p = new LoginClient(this);
    p->show();
    this->hide();
}

void ForgetPasClient::on_pushButton_clicked()
{
    string User = ui->textEdit->toPlainText().toStdString();
    string Cell = ui->textEdit_2->toPlainText().toStdString();
    if(MatchingUserAndCellClient( User, Cell)&&User!=""&&Cell!="")
    {
        RecoveryPasClient *p = new RecoveryPasClient(this);
        p->show();
        this->hide();
    }
    else
    {
        QMessageBox::about(this,"توجه","یوزر یا شماره تلفن تطابقت ندارد یا دو جایگاه خالیست");
        return;
    }

}

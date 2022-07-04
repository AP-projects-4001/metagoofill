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
    return true;
}
bool Check(string Username,string Number)
{
       class client Client;
       ifstream clientFile("clients.txt", ios::in | ios::binary);
       string user;
       string number;
       while(clientFile.read((char*)&Client,sizeof(client)))
       {
           Client.char_array_to_string(user, 16, Client.User);
           Client.char_array_to_string(number, 31, Client.CellPhoneNumber);
           if(Username == user)
           {
               if(Number == number)
               {
                   return true;
               }
           }
       }
        return false;
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

void ForgetPasClient::Getpas(QString m)
{
    string User = cli_tmp.User;
    string username_tmp = "";
    fstream Cli_tmps("clients.txt", ios::in | ios::out | ios::binary);
    while(Cli_tmps.read((char*)&cli_tmp, sizeof(client)))
    {
        cli_tmp.char_array_to_string(username_tmp, 16, cli_tmp.User);
        if(username_tmp == User)
        {
            cli_tmp.string_to_char_array(cli_tmp.Password,16,m.toStdString());
            Cli_tmps.seekp(-sizeof(client),ios::cur);
            Cli_tmps.write((char*)&cli_tmp,sizeof(client));//جایگزین کردن اطلاعات
            break;
        }
    }
}

void ForgetPasClient::on_pushButton_clicked()
{
    string User = ui->textEdit->toPlainText().toStdString();
    string Number = ui->textEdit_2->toPlainText().toStdString();
    string username_tmp = "";
    if(Check(User, Number) && User != "" && Number != "")
    {
        QMessageBox::about(this, "توجه", "ورود موفقیت آمیز");
        fstream Cli_tmps("clients.txt", ios::in | ios::out | ios::binary);
        while(Cli_tmps.read((char*)&cli_tmp,sizeof(client)))
        {
            cli_tmp.char_array_to_string(username_tmp, 16, cli_tmp.User);
            if(username_tmp == User)
            {

                RecoveryPasClient *p = new RecoveryPasClient(this);
                connect(p,SIGNAL(passPas(QString)),this,SLOT(Getpas(QString)));
                p->show();
                break;
            }
        }
       Cli_tmps.close();
    }
}

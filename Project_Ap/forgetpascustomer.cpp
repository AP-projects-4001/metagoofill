#include "forgetpascustomer.h"
#include "ui_forgetpascustomer.h"

using namespace std;
ForgetPasCustomer::ForgetPasCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgetPasCustomer)
{
    ui->setupUi(this);
}
bool MatchingUserAndCellCustomer(string Username,string Number)
{
    class customer Customer;
    ifstream CustomerFile("customers.txt", ios::in | ios::binary);
    string user;
    string number;
    while(CustomerFile.read((char*)&Customer, sizeof(customer)))
    {
        Customer.char_array_to_string(user, 16, Customer.get_User());
        Customer.char_array_to_string(number, 31, Customer.get_phoneNumber());
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
ForgetPasCustomer::~ForgetPasCustomer()
{
    delete ui;
}

void ForgetPasCustomer::on_pushButton_clicked()
{
    string User = ui->textEdit->toPlainText().toStdString();
    string Number = ui->textEdit_2->toPlainText().toStdString();
    string username_tmp = "";
    if(MatchingUserAndCellCustomer(User, Number) && User != "" && Number != "")
    {

        fstream cus_tmps("customers.txt", ios::in | ios::out | ios::binary);
        while(cus_tmps.read((char*)&Cus_tmp,sizeof(customer)))
        {
            Cus_tmp.char_array_to_string(username_tmp, 16, Cus_tmp.get_User());

            if(username_tmp == User)
            {

                RecoveryPasCustomer *p = new RecoveryPasCustomer(this);
                connect(p,SIGNAL(PassingTheCustomerPassword(QString)),this,
                        SLOT(GetNewPasCus(QString)));
                p->show();
                break;
            }
        }
       cus_tmps.close();
    }
}

void ForgetPasCustomer::on_pushButton_2_clicked()
{
    CustomerLogin *p = new CustomerLogin(this);
    p->show();
    this->hide();
}

void ForgetPasCustomer::GetNewPasCus(QString m)
{
    qDebug("Failed to write the data to port");
    string User = Cus_tmp.get_User();
    string username_tmp = "";
    fstream cus_tmps("customers.txt", ios::in | ios::out | ios::binary);
    while(cus_tmps.read((char*)&Cus_tmp, sizeof(customer)))
    {
        Cus_tmp.char_array_to_string(username_tmp, 16, Cus_tmp.get_User());
        if(username_tmp == User)
        {
            Cus_tmp.string_to_char_array(Cus_tmp.get_Password(),16,m.toStdString());
            cus_tmps.seekp(-sizeof(customer),ios::cur);
            cus_tmps.write((char*)&Cus_tmp,sizeof(customer));//جایگزین کردن اطلاعات
            break;
        }
    }
}

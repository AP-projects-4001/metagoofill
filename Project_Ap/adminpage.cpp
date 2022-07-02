#include "adminpage.h"
#include "ui_adminpage.h"
#include "listofcustomersforadmin.h"
#include "mainlogin.h"
#include "listofclientforadmin.h"
AdminPage::AdminPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
}

AdminPage::~AdminPage()
{
    delete ui;
}

void AdminPage::on_pushButton_2_clicked()
{
    close();
    listoftransactions *p = new listoftransactions(this);
    p->show();
}

void AdminPage::on_pushButton_clicked()
{
    close();
    ListOfCustomersForAdmin *p = new ListOfCustomersForAdmin(this);
    p->show();
}

void AdminPage::on_pushButton_3_clicked()
{
    close();
    MainLogin *p = new MainLogin(this);
    p->show();
}

void AdminPage::on_pushButton_4_clicked()
{
    close();
    ListOFClientForAdmin *p = new ListOFClientForAdmin(this);
    p->show();
//    this->hide();
}

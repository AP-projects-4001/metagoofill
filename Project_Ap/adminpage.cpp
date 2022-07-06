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
    this->close();
    listoftransactions *p = new listoftransactions();
    p->show();
}

void AdminPage::on_pushButton_clicked()
{
    this->close();
    ListOfCustomersForAdmin *p = new ListOfCustomersForAdmin();
    p->show();
}

void AdminPage::on_pushButton_3_clicked()
{
    this->close();
    MainLogin *p = new MainLogin();
    p->show();
}

void AdminPage::on_pushButton_4_clicked()
{
    this->close();
    ListOFClientForAdmin *p = new ListOFClientForAdmin();
    p->show();
}

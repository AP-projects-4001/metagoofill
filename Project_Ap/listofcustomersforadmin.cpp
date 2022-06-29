#include "listofcustomersforadmin.h"
#include "ui_listofcustomersforadmin.h"
#include "adminpage.h"
ListOfCustomersForAdmin::ListOfCustomersForAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListOfCustomersForAdmin)
{
    ui->setupUi(this);
    this->setWindowTitle("لیست فروشندگان");
    QString content = "نمایش فروشندگان";
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}

ListOfCustomersForAdmin::~ListOfCustomersForAdmin()
{
    delete ui;
}

void ListOfCustomersForAdmin::on_pushButton_2_clicked()
{
    close();
    AdminPage *p = new AdminPage(this);
    p->show();
}

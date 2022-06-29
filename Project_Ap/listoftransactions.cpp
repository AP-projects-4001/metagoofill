#include "listoftransactions.h"
#include "ui_listoftransactions.h"
#include "adminpage.h"
listoftransactions::listoftransactions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listoftransactions)
{
    ui->setupUi(this);
    this->setWindowTitle("لیست تراکنش ها");
    QString content = "نمایش تراکنش ها";
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}

listoftransactions::~listoftransactions()
{
    delete ui;
}

void listoftransactions::on_pushButton_clicked()
{
    close();
    AdminPage *p = new AdminPage(this);
    p->show();
}

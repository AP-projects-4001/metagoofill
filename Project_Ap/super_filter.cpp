#include "super_filter.h"
#include "ui_super_filter.h"

super_filter::super_filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::super_filter)
{
    ui->setupUi(this);
}

super_filter::~super_filter()
{
    delete ui;
}

void super_filter::on_pushButton_2_clicked()
{
    super_info.set_name_prod(ui->lineEdit->text().toStdString());
    super_info.set_price_from(ui->lineEdit_2->text().toStdString());
    super_info.set_price_to(ui->lineEdit_5->text().toStdString());
    super_info.set_customer_name(ui->lineEdit_3->text().toStdString());
    super_info.set_grouping(ui->comboBox->currentText().toStdString());
    super_info.set_color(ui->lineEdit_6->text().toStdString());

    emit send_super_info(super_info);
    this->close();
}


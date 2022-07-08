#include "homeapps_filter.h"
#include "ui_homeapps_filter.h"

homeApps_filter::homeApps_filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homeApps_filter)
{
    ui->setupUi(this);
}

homeApps_filter::~homeApps_filter()
{
    delete ui;
}

void homeApps_filter::on_pushButton_2_clicked()
{
    homeapp_info.name_prod = ui->lineEdit->text().toStdString();
    homeapp_info.price_from = ui->lineEdit_2->text().toStdString();
    homeapp_info.price_to = ui->lineEdit_5->text().toStdString();
    homeapp_info.customer_name = ui->lineEdit_3->text().toStdString();
    homeapp_info.grouping = ui->comboBox->currentText().toStdString();
    homeapp_info.color = ui->lineEdit_6->text().toStdString();

    emit send_homeapp_info(homeapp_info);
    this->close();
}


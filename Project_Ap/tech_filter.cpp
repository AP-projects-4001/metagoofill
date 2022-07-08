#include "tech_filter.h"
#include "ui_tech_filter.h"

tech_filter::tech_filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tech_filter)
{
    ui->setupUi(this);
}

tech_filter::~tech_filter()
{
    delete ui;
}

void tech_filter::on_pushButton_2_clicked()
{
    tech_info.name_prod = ui->lineEdit->text().toStdString();
    tech_info.price_from = ui->lineEdit_2->text().toStdString();
    tech_info.price_to = ui->lineEdit_5->text().toStdString();
    tech_info.customer_name = ui->lineEdit_3->text().toStdString();
    tech_info.grouping = ui->comboBox->currentText().toStdString();
    tech_info.color = ui->lineEdit_6->text().toStdString();

    emit send_tech_info(tech_info);
    this->close();
}


#include "dialog_options.h"
#include "ui_dialog_options.h"

Dialog_options::Dialog_options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_options)
{
    ui->setupUi(this);
}

Dialog_options::~Dialog_options()
{
    delete ui;
}

void Dialog_options::on_buttonBox_accepted()
{
    emit item_added(ui->checkBox_berand->isChecked(),ui->checkBox_color->isChecked(),ui->checkBox_weight->isChecked(),ui->radioButton_1->isChecked());
}

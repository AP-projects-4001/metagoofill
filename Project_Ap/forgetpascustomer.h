#ifndef FORGETPASCUSTOMER_H
#define FORGETPASCUSTOMER_H
#include<QMessageBox>
#include <fstream>
#include <QDialog>
#include "recoverypascustomer.h"
#include "customerlogin.h"
#include "mainlogin.h"

namespace Ui {
class ForgetPasCustomer;
}

class ForgetPasCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit ForgetPasCustomer(QWidget *parent = nullptr);
    ~ForgetPasCustomer();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void GetNewPasCus(QString);

private:
    Ui::ForgetPasCustomer *ui;
    class customer Cus_tmp;
};

#endif // FORGETPASCUSTOMER_H
